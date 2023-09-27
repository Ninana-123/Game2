#include "pch.h"
#include "Graphics.h"
#include "logger.h"

namespace Engine
{
    Logger GraphicsLogger;

    Graphics::Graphics()
        : shader("Resource/Shaders/Basic.shader")
        
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

        Window = glfwGetCurrentContext();

        Graphics::InitializeGLEW();

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        // Clear the color buffer
        glClear(GL_COLOR_BUFFER_BIT);

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
        InitialiseShader();

        // initialize and bind textures
        InitialiseTextures();

        ib.Unbind();
        va.Unbind();
        vb.Unbind();
        shader.Unbind();
    }


    void Graphics::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
    {
        renderer.Clear();

        for (const auto& entityPair : *entities)
        {
            Entity* entity = entityPair.second.get();

            if (entity->HasComponent(ComponentType::Transform))
            {
                //Assign reference to transform component
                TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
                //Read transform data from component
                 
                //translate
                glm::vec3 transA(transform->x, transform->y, 0);
           
                //rotate
                float rotation = transform->rot;

                //scale
                glm::vec3 scale1(transform->scaleX, transform->scaleY, 1.0f);

                int width, height;
                glfwGetWindowSize(Window, &width, &height);
                UpdateViewport(width, height);

               
                //// Get the current state of the 'P' key
                //bool currentPState = glfwGetKey(this->Window, GLFW_KEY_P) == GLFW_PRESS;

                //// Check if there's a change in the 'P' key state
                //if (currentPState && !previousPState)
                //{
                //    // Toggle the rendering mode
                //    ToggleRenderMode();
                //}

                //// Update the previous 'P' key state
                //previousPState = currentPState;

                /*if (renderTexturedSquare)
                {*/
                //Texture A
                {
                    /*
                    * UpdateTransformations(GLFW_KEY_RIGHT, transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_LEFT,  transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_UP,    transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_DOWN,  transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_U,     transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_I,     transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_Z,     transA, scale1, rotation);
                    UpdateTransformations(GLFW_KEY_X,     transA, scale1, rotation);
                    */
                    

                    // Apply transformations from UpdateTransformations
                    glm::mat4 modelA = glm::mat4(1.0f); // Initialize the model matrix as identity
                    modelA = glm::translate(modelA, transA);
                    modelA = glm::scale(modelA, scale1);
                    modelA = glm::rotate(modelA, rotation, glm::vec3(0.0f, 0.0f, 1.0f));

                    glm::mat4 mvpA = proj * view * modelA;

                    shader.Bind();
                    //luffyTexture.Bind(0);

                    double currentTime = glfwGetTime();
                    double elapsedTime = currentTime - programStartTime;
                    int textureIndex = static_cast<int>(elapsedTime / 3.0) % 2;

                    if (textureIndex == 0)
                    {
                        // Display "Luffy" texture
                        textureA.Bind(0);
                    }
                    else
                    {
                        // Display "Zoro" texture
                        textureB.Bind(0);
                    }

                    // Set shader uniforms for Luffy
                    shader.SetUniform1i("u_RenderTextured", 1); // Render textured
                    shader.SetUniform1i("u_Texture", 0);
                    shader.SetUniformMat4f("u_MVP", mvpA);
                    renderer.Draw(va, ib, shader);

                    // Draw a square around Texture A
                    shader.SetUniform1i("u_RenderTextured", 0); // Render plain (no texture)
                    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f); // Set the line color

                    // Draw the square as lines 
                    GLCall(glDrawArrays(GL_LINE_LOOP, 0, 4));

                    // Reset the shader render mode to textured
                    shader.SetUniform1i("u_RenderTextured", 1);

                }

                //}
                //else
                //{
                //    // translation vector for the blue square's position
                //    glm::vec3 blueSquareTranslation = glm::vec3(600.0f, 200.0f, 0.0f); // Modify the values as needed

                //    // model matrix with the new translation
                //    glm::mat4 model = glm::mat4(1.0f); // Identity matrix
                //    model = glm::translate(model, blueSquareTranslation);

                //    // Calculate the MVP matrix
                //    glm::mat4 mvp = proj * view * model;

                //    // Bind the shader and set uniforms
                //    shader.Bind();
                //    shader.SetUniform4f("u_Color", 0.0f, 0.0f, 0.0f, 1.0f);
                //    shader.SetUniformMat4f("u_MVP", mvp);

                //    // Render the blue square
                //    renderer.Draw(va, ib, shader);
                //}
                transform->x = transA.x;
                transform->y = transA.y;
            }

        }
        GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }

    void Graphics::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }

    void Graphics::InitialiseShader()
    {
        shader.LoadShader("Resource/Shaders/Basic.shader");
        shader.Initialize();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);
    }

    void Graphics::InitialiseTextures()
    {
        textureA.Load("Resource/Texture/Tank.png");
        textureB.Load("Resource/Texture/Archer.png");

        textureA.InitGL();
        textureA.Bind(0);

        textureB.InitGL();
        textureB.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)
    }


    void Graphics::UpdateTransformations(int key, glm::vec3 translation, glm::vec3 scale, float rotation)
    {
        // Define a mapping of keys to actions
        std::map<int, std::function<void()>> keyActions;

        const float increment = 1.0f;
        const float angle = 0.01f;
        const float scalar = 0.01f;

        // Texture A 
        keyActions[GLFW_KEY_RIGHT] = [&]()
        {
            translation.x += increment; //Move right 
        };

        keyActions[GLFW_KEY_LEFT] = [&]()
        {
            translation.x -= increment; //Move left
        };

        keyActions[GLFW_KEY_DOWN] = [&]()
        {
            translation.y -= increment; //Move down
        };

        keyActions[GLFW_KEY_UP] = [&]()
        {
            translation.y += increment; //Move up
        };

        keyActions[GLFW_KEY_U] = [&]()
        {
            rotation += angle; //Rotate counterclockwise
        };

        keyActions[GLFW_KEY_I] = [&]()
        {
            rotation -= angle; //Rotate clockwise
        };
        keyActions[GLFW_KEY_Z] = [&]()
        {
            scale += glm::vec3(scalar, scalar, 0.0f); //Increase scale
        };

        keyActions[GLFW_KEY_X] = [&]()
        {
            scale -= glm::vec3(scalar, scalar, 0.0f); //Decrease scale
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

    // Function to toggle between textured and plain squares
    void Graphics::ToggleRenderMode()
    {
        renderTexturedSquare = !renderTexturedSquare;
        shader.Bind();
        shader.SetUniform1i("u_RenderTextured", renderTexturedSquare ? 1 : 0);
    }

    glm::mat4 Graphics::SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale)
    {
        glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix as identity
        model = glm::translate(model, translation);
        model = glm::scale(model, scale);
        model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        return model;
    }

} // namespace Engine