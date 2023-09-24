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

        //for (int i = 0; i < totalFrames; ++i) {
        //    std::string frameTexturePath = "Resource/Texture/Luffy" + std::to_string(i) + ".png";
        //    Texture frameTexture(frameTexturePath);
        //    frameTexture.InitGL();
        //    luffyFrames.push_back(frameTexture);
        //}

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
 
    void Graphics::Update(Entity* entity)
    {
        if (entity->HasComponent(ComponentType::Transform))
        {   

        }
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        UpdateViewport(width, height);

        // Handle graphics updates here
        renderer.Clear();

        //double currentTime = glfwGetTime();
        //static double lastTime = 0.0;

        //// Calculate time elapsed since the last frame
        //double deltaTime = currentTime - lastTime;
        //lastTime = currentTime;

        //frameTimer += static_cast<float>(deltaTime); // Update the frame timer

        //if (frameTimer >= frameDuration)
        //{
        //    frameTimer = 0.0f;
        //    currentFrame = (currentFrame + 1) % totalFrames;
        //}

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

            glm::mat4 model = glm::mat4(1.0f); // Initialize the model matrix as identity

            // Apply transformations from UpdateTransformations
            model = glm::translate(model, translationA);
            model = glm::scale(model, scaleA);
            model = glm::rotate(model, rotationAngleA, glm::vec3(0.0f, 0.0f, 1.0f));

            glm::mat4 mvp = proj * view * model;
            shader.Bind();
            luffyTexture.Bind(0);
            //luffyFrames[currentFrame].Bind(0); // Bind the current animation frame
            shader.SetUniform1i("u_Texture", 0);
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
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

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB); // Right translation
            model = glm::scale(model, scaleB); // Apply scaling
            model = glm::rotate(model, rotationAngleB, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis

            glm::mat4 mvp = proj * view * model;

            zoroTexture.Bind(1);
            shader.Bind();

            shader.SetUniform1i("u_Texture", 1);
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        //// Texture C
        //{
        //    shader.SetUniform1i("u_Texture", 2); // Use a different texture unit (e.g., unit 2)

        //    UpdateTransformations(GLFW_KEY_M); // Customize the key for Texture C transformations

        //    glm::mat4 model = glm::translate(glm::mat4(1.0f), translationC); // Customize the translation
        //    model = glm::scale(model, scaleC); // Customize the scale
        //    model = glm::rotate(model, rotationAngleC, glm::vec3(0.0f, 0.0f, 1.0f)); // Customize the rotation

        //    glm::mat4 mvp = proj * view * model;

        //    // Bind Texture C
        //    textureC.Bind(2); // Bind your Texture C to texture unit 2

        //    shader.Bind();

        //    shader.SetUniform1i("u_Texture", 2); // Set the uniform to use texture unit 2
        //    shader.SetUniformMat4f("u_MVP", mvp);

        //    renderer.Draw(va, ib, shader);
        //}

        //GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }

    void Graphics::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }
} // namespace Engine