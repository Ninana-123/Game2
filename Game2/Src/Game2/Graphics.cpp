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

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va{};
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        Graphics::va.AddBuffer(vb, layout);

        Graphics::ib.SetData(indices, 6);

        // Moving of the texture
        Graphics::proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        Graphics::view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)); // Left translation
        shader.LoadShader("Resource/Shaders/Basic.shader");
        shader.Initialize();
        shader.Bind();
        shader.SetUniform4f("u_Color", 1.0f, 1.0f, 1.0f, 1.0f);

        luffyTexture.InitGL();
        luffyTexture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);

        zoroTexture.InitGL();
        zoroTexture.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)

        ib.Unbind();
        va.Unbind();
        vb.Unbind();
        shader.Unbind();
    }

    void Graphics::Update()
    {
        int width, height;
        glfwGetWindowSize(Window, &width, &height);
        UpdateViewport(width, height);
        // Handle graphics updates here
        renderer.Clear();

        // Define a mapping of keys to actions
        std::map<int, std::function<void()>> keyActions;

        // Initialize the mapping
        keyActions[GLFW_KEY_RIGHT] = [&]() { translationA.x += 5.0f; }; //Move right for texture  A
        keyActions[GLFW_KEY_D]     = [&]() { translationB.x += 5.0f; }; //Move right for texture  B
        keyActions[GLFW_KEY_LEFT]  = [&]() { translationA.x -= 5.0f; }; //Move left  for texture  A
        keyActions[GLFW_KEY_A]     = [&]() { translationB.x -= 5.0f; }; //Move left  for texture  B
        keyActions[GLFW_KEY_DOWN]  = [&]() { translationA.y -= 5.0f; }; //Move down  for texture  A
        keyActions[GLFW_KEY_S]     = [&]() { translationB.y -= 5.0f; }; //Move down  for texture  B
        keyActions[GLFW_KEY_UP]    = [&]() { translationA.y += 5.0f; }; //Move up    for texture  A
        keyActions[GLFW_KEY_W]     = [&]() { translationB.y += 5.0f; }; //Move up    for texture  B
        keyActions[GLFW_KEY_U]     = [&]() { rotationAngleA += 0.1f; }; // Rotate texture A counterclockwise
        keyActions[GLFW_KEY_I]     = [&]() { rotationAngleA -= 0.1f; }; // Rotate texture A clockwise
        keyActions[GLFW_KEY_J]     = [&]() { rotationAngleB += 0.1f; }; // Rotate texture B counterclockwise
        keyActions[GLFW_KEY_K]     = [&]() { rotationAngleB -= 0.1f; }; // Rotate texture B clockwise
        keyActions[GLFW_KEY_Z]     = [&]() { scaleA += glm::vec3(0.1f, 0.1f, 0.0f); }; // Increase scale for texture A
        keyActions[GLFW_KEY_X]     = [&]() { scaleA -= glm::vec3(0.1f, 0.1f, 0.0f); }; // Decrease scale for texture A
        keyActions[GLFW_KEY_C]     = [&]() { scaleB += glm::vec3(0.1f, 0.1f, 0.0f); }; // Increase scale for texture B
        keyActions[GLFW_KEY_V]     = [&]() { scaleB -= glm::vec3(0.1f, 0.1f, 0.0f); }; // Decrease scale for texture B

        // Check for key presses and execute corresponding actions
        for (const auto& pair : keyActions)
        {
            if (glfwGetKey(this->Window, pair.first) == GLFW_PRESS)
            {
                pair.second();
            }
        }

        //Texture A
        {
            //shader.SetUniform1i("u_Texture", 0);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA);  // Left translation
            model = glm::scale(model, scaleA); // Apply scaling
            model = glm::rotate(model, rotationAngleA, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis

            glm::mat4 mvp = proj * view * model;

            luffyTexture.Bind(0);
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        //Texture B
        {
            //shader.SetUniform1i("u_Texture", 1);

            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB); // Right translation
            model = glm::scale(model, scaleB); // Apply scaling
            model = glm::rotate(model, rotationAngleB, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis
            glm::mat4 mvp = proj * view * model;
            zoroTexture.Bind(1);
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        // Increment the rotation angle for animation
        //Graphics::rotationAngle += 0.05f;

        GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");
    }

    void Graphics::UpdateViewport(int width, int height)
    {
        glViewport(0, 0, width, height);
        proj = glm::ortho(0.0f, static_cast<float>(width), 0.0f, static_cast<float>(height), -1.0f, 1.0f);
    }
} // namespace Engine