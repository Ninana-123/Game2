#include "pch.h"
#include "Graphics.h"
#include "logger.h"

namespace Engine
{
    Logger GraphicsLogger;

    Graphics::Graphics()
        : shader("Resource/Shaders/Basic.shader"),luffyTexture("Resource/Texture/Luffy.png"),zoroTexture("Resource/Texture/zoro.png")
    {
        Window = glfwGetCurrentContext();
        InitializeGLEW();
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
        float positions[] =
        {
            -50.0f, -50.0f, 0.0f, 0.0f, // 0
            50.0f, -50.0f, 1.0f, 0.0f, // 1
            50.0f, 50.0f, 1.0f, 1.0f, // 2
            -50.0f, 50.0f, 0.0f, 1.0f // 3
        };


        // Copy vtx_position into vtx_position member variable
        std::copy(std::begin(positions), std::end(positions), std::begin(this->vtx_postions));

        unsigned int indices[] =
        {
            0, 1, 2,
            2, 3, 0
        };

        std::copy(std::begin(indices), std::end(indices), std::begin(this->indices));
        glm::vec3 transA(200, 200, 0);
        translationA = transA;
        glm::vec3 transB(400, 200, 0);
        translationB = transB;

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
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
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
        luffyTexture.InitGL();
        luffyTexture.Bind(0);
        shader.SetUniform1i("u_Texture", 0);
        zoroTexture.InitGL();
        zoroTexture.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();
    }

    void Graphics::Update()
    {
        if (!Window)
        {
            // Handle the case where the window creation failed
            return;
        }

        // Handle graphics updates here
        renderer.Clear();
        // Handle keyboard input
        if (glfwGetKey(this->Window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        {
            // Right arrow key is pressed, move right
            translationA.x += 5.0f;
        }
        if (glfwGetKey(this->Window, GLFW_KEY_LEFT) == GLFW_PRESS)
        {
            // Left arrow key is pressed, move left
            translationA.x -= 5.0f;
        }
        if (glfwGetKey(this->Window, GLFW_KEY_DOWN) == GLFW_PRESS)
        {
            // Down arrow key is pressed, move down
            translationA.y -= 5.0f;
        }
        if (glfwGetKey(this->Window, GLFW_KEY_UP) == GLFW_PRESS)
        {
            // UP arrow key is pressed, move UP
            translationA.y += 5.0f;
        }

        // Check for "R" key press
        if (glfwGetKey(this->Window, GLFW_KEY_R) == GLFW_PRESS)
        {
            // "R" key is pressed, increment rotation angle
            rotationAngle += 0.05f;
        }


        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationA); // Left translation
            model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis
            glm::mat4 mvp = proj * view * model;
            luffyTexture.Bind(0);
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), translationB); // Right translation
            model = glm::rotate(model, rotationAngle, glm::vec3(0.0f, 0.0f, 1.0f)); // Rotate around the Z-axis
            glm::mat4 mvp = proj * view * model;
            zoroTexture.Bind(1);
            shader.Bind();
            shader.SetUniformMat4f("u_MVP", mvp);
            renderer.Draw(va, ib, shader);
        }


        // Increment the rotation angle for animation
        Graphics::rotationAngle += 0.05f;

        /* Swap front and back buffers */
        glfwSwapBuffers(this->Window);

        /* Poll for and process events */
        glfwPollEvents();
        GraphicsLogger.Log(LogLevel::Debug, "Currently updating graphics");

    }


	

} // namespace Engine
