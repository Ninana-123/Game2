#include "pch.h"
#include "Graphics.h"
#include "logger.h"

namespace Engine
{
    Logger GraphicsLogger;

    Graphics::Graphics()
        : shader("Resource/Shaders/Basic.shader"),
        luffyTexture("Resource/Texture/Luffy.png"),
        zoroTexture("Resource/Texture/zoro.png")
    {
    }

    Graphics::~Graphics()
    {
        // Cleanup any resources here
        // Terminate GLFW
        glfwTerminate();
    }

    void Graphics::InitializeGLEW() {
        // Initialize GLEW
        GLenum glewInitResult = glewInit();
        if (glewInitResult != GLEW_OK)
        {
            GraphicsLogger.Log(LogLevel::Error, "GLEW failed to initialize");
            glfwTerminate();
        }
        else
            GraphicsLogger.Log(LogLevel::Debug, "GLEW successfully initialized");
    }

    void Graphics::Initialize() {
        //define vertex array and indices
        float positions[] = {
       -50.0f,  -50.0f, 0.0f, 0.0f,    //0
        50.0f,  -50.0f, 1.0f, 0.0f,    //1
        50.0f,   50.0f, 1.0f, 1.0f,    //2
       -50.0f,   50.0f, 0.0f, 1.0f     //3
        };

        // Copy vtx_position into vtx_position member variable
        std::copy(std::begin(positions), std::end(positions), std::begin(this->vtx_postions));

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        std::copy(std::begin(indices), std::end(indices), std::begin(this->indices));

        //Translation for A and B
        glm::vec3 transA(200, 200, 0);
        translationA = transA;
        glm::vec3 transB(400, 200, 0);
        translationB = transB;

        // Rotation angles for textures A and B
        rotationAngleA = 0.0f; // Initial rotation angle 
        rotationAngleB = 0.0f;

        //Scale for A and B
        glm::vec3 scale1(1.0f, 1.0f, 1.0f); //initial scale
        glm::vec3 scale2(1.0f, 1.0f, 1.0f);
        scaleA = scale1;
        scaleB = scale2;

        //enable blending for transparency
        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        //create vertex array, vertex buffer, and index buffer
        VertexArray va{};
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        Graphics::va.AddBuffer(vb, layout);

        Graphics::ib.SetData(indices, 6);

        // set up projection and view matrices
        Graphics::proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        Graphics::view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation

        // load and initialize the shader
        shader.LoadShader("Resource/Shaders/Basic.shader");
        shader.Initialize();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        // initialize and bind textures
        luffyTexture.InitGL();
        luffyTexture.Bind(0);

        zoroTexture.InitGL();
        zoroTexture.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)

        ib.Unbind();
        va.Unbind();
        vb.Unbind();
        shader.Unbind();
    }

    void Graphics::UpdateTransformations(int key)
    {
        // Define a mapping of keys to actions
        std::map<int, std::function<void()>> keyActions;

        const float increment = 1.0f;
        const float angle = 0.01f;
        const float scale = 0.01f;

        // Texture A 
        keyActions[GLFW_KEY_RIGHT] = [&]()
            {
                translationA.x += increment; //Move right 
            };

        keyActions[GLFW_KEY_LEFT] = [&]()
            {
                translationA.x -= increment; //Move left
            };

        keyActions[GLFW_KEY_DOWN] = [&]()
            {
                translationA.y -= increment; //Move down
            };

        keyActions[GLFW_KEY_UP] = [&]()
            {
                translationA.y += increment; //Move up
            };

        keyActions[GLFW_KEY_U] = [&]()
            {
                rotationAngleA += angle; //Rotate counterclockwise
            };

        keyActions[GLFW_KEY_I] = [&]()
            {
                rotationAngleA -= angle; //Rotate clockwise
            };
        keyActions[GLFW_KEY_Z] = [&]()
            {
                scaleA += glm::vec3(scale, scale, 0.0f); //Increase scale
            };

        keyActions[GLFW_KEY_X] = [&]()
            {
                scaleA -= glm::vec3(scale, scale, 0.0f); //Decrease scale
            };

        // Texture B
        keyActions[GLFW_KEY_D] = [&]()
            {
                translationB.x += increment; //Move right
            };

        keyActions[GLFW_KEY_A] = [&]()
            {
                translationB.x -= increment; //Move left
            };

        keyActions[GLFW_KEY_S] = [&]()
            {
                translationB.y -= increment; //Move down
            };

        keyActions[GLFW_KEY_W] = [&]()
            {
                translationB.y += increment; //Move up
            };

        keyActions[GLFW_KEY_J] = [&]()
            {
                rotationAngleB += angle; // Rotate texture
            };

        keyActions[GLFW_KEY_K] = [&]()
            {
                rotationAngleB -= angle; // Rotate texture
            };

        keyActions[GLFW_KEY_C] = [&]()
            {
                scaleB += glm::vec3(scale, scale, 0.0f); // Increase scale
            };

        keyActions[GLFW_KEY_V] = [&]()
            {
                scaleB -= glm::vec3(scale, scale, 0.0f); // Decrease scale
            };

        // Check for key presses and execute corresponding actions
        for (const auto& pair : keyActions)
        {
            if (glfwGetKey(this->Window, pair.first) == GLFW_PRESS)
            {
                pair.second();
            }
        }
    }

    void Graphics::Update()
    {
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        UpdateViewport(width, height);

        // Handle graphics updates here
        renderer.Clear();

        // Get the current state of the 'P' key
        bool currentPState = glfwGetKey(this->Window, GLFW_KEY_P) == GLFW_PRESS;

        // Check if there's a change in the 'P' key state
        if (currentPState && !previousPState)
        {
            // Toggle between textured and plain squares when the 'P' key is pressed
            renderTexturedSquare = !renderTexturedSquare;
            shader.Bind();
            if (renderTexturedSquare)
            {
                shader.SetUniform1i("u_RenderTextured", 1); // Render textured
            }
            else
            {
                shader.SetUniform1i("u_RenderTextured", 0); // Render plain
            }
        }

        // Update the previous 'P' key state
        previousPState = currentPState;


      
        if (renderTexturedSquare)
        {
            //Texture A
            {
                UpdateTransformations(GLFW_KEY_RIGHT);
                UpdateTransformations(GLFW_KEY_LEFT);
                UpdateTransformations(GLFW_KEY_UP);
                UpdateTransformations(GLFW_KEY_DOWN);
                UpdateTransformations(GLFW_KEY_U);
                UpdateTransformations(GLFW_KEY_I);
                UpdateTransformations(GLFW_KEY_Z);
                UpdateTransformations(GLFW_KEY_X);

                // Calculate the model matrix for Texture A
                glm::mat4 modelA = glm::mat4(1.0f); // Initialize the model matrix as identity
                modelA = glm::translate(modelA, translationA);
                modelA = glm::scale(modelA, scaleA);
                modelA = glm::rotate(modelA, rotationAngleA, glm::vec3(0.0f, 0.0f, 1.0f));

                // Calculate the MVP matrix for Texture A
                glm::mat4 mvpA = proj * view * modelA;
                
                shader.Bind();
                luffyTexture.Bind(0);

                // Set shader uniforms for Luffy
                shader.SetUniform1i("u_RenderTextured", 1); // Render textured
                shader.SetUniform1i("u_Texture", 0);
                shader.SetUniformMat4f("u_MVP", mvpA);

                
                renderer.Draw(va, ib, shader);

                // Draw a square around Texture A
                shader.SetUniform1i("u_RenderTextured", 0); // Render plain (no texture)
                shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f); // Set the line color

                // Calculate the MVP matrix for the square around Texture A
               // glm::mat4 modelSquareA = glm::mat4(1.0f);
                /*modelSquareA = glm::translate(modelSquareA, translationA);
                modelSquareA = glm::scale(modelSquareA, scaleA);
                modelSquareA = glm::rotate(modelSquareA, rotationAngleA, glm::vec3(0.0f, 0.0f, 1.0f));
                glm::mat4 mvpSquareA = proj * view * modelSquareA;*/
               // shader.SetUniformMat4f("u_MVP", mvpSquareA);

                // Draw the square as lines (4 vertices, primitive type GL_LINE_LOOP)
                GLCall(glDrawArrays(GL_LINE_LOOP, 0, 4));

                // Reset the shader render mode to textured
                shader.SetUniform1i("u_RenderTextured", 1);
            }




            //Texture B
            {
                UpdateTransformations(GLFW_KEY_W);
                UpdateTransformations(GLFW_KEY_A);
                UpdateTransformations(GLFW_KEY_S);
                UpdateTransformations(GLFW_KEY_D);
                UpdateTransformations(GLFW_KEY_J);
                UpdateTransformations(GLFW_KEY_K);
                UpdateTransformations(GLFW_KEY_C);
                UpdateTransformations(GLFW_KEY_V);

                // Calculate the model matrix for Texture B
                glm::mat4 modelB = glm::translate(glm::mat4(1.0f), translationB); // Right translation
                modelB = glm::scale(modelB, scaleB); // Apply scaling
                modelB = glm::rotate(modelB, rotationAngleB, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis

                // Calculate the MVP matrix for Texture B
                glm::mat4 mvpB = proj * view * modelB;

                // Bind the shader for Texture B
                shader.Bind();
                zoroTexture.Bind(1);

                // Set shader uniforms for Texture B
                shader.SetUniform1i("u_RenderTextured", 1); // Render textured
                shader.SetUniform1i("u_Texture", 1);
                shader.SetUniformMat4f("u_MVP", mvpB);

                // Render Texture B
                renderer.Draw(va, ib, shader);

                // Draw a square around Texture B
                shader.SetUniform1i("u_RenderTextured", 0); // Render plain (no texture)
                shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f); // Set the line color

                // Draw the square as lines (4 vertices, primitive type GL_LINE_LOOP)
                GLCall(glDrawArrays(GL_LINE_LOOP, 0, 4));

                // Reset the shader render mode to textured
                shader.SetUniform1i("u_RenderTextured", 1);
            }



        }
        else
        {
            // translation vector for the blue square's position
            glm::vec3 blueSquareTranslation = glm::vec3(600.0f, 200.0f, 0.0f); // Modify the values as needed

            // model matrix with the new translation
            glm::mat4 model = glm::mat4(1.0f); // Identity matrix
            model = glm::translate(model, blueSquareTranslation);

            // Calculate the MVP matrix
            glm::mat4 mvp = proj * view * model;

            // Bind the shader and set uniforms
            shader.Bind();
            shader.SetUniform4f("u_Color", 0.0f, 0.0f, 1.0f, 1.0f);
            shader.SetUniformMat4f("u_MVP", mvp);

            // Render the blue square
            renderer.Draw(va, ib, shader);
        }


        //GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }

    void Graphics::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }
} // namespace Engine