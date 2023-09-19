#include "pch.h"

#include "Graphics.h"
#include "Application.h"
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Input.h"
#include "EntityManager.h"
#include "PositionComponent.h"
#include "Entity.h"
#include "System.h"
#include "KeyCodes.h"

double fps = 0.00;  // Frames per second
double previousTime = glfwGetTime();  // Previous time for FPS calculation
double dt = 0.0;  // Time difference between frames (delta time)

glm::mat4 proj, view;

namespace Engine
{
    // Create a logger instance
    Engine::Logger logger;
    Engine::EntityManager EM;
    EntityID entity1 = EM.CreateEntity();
    EntityID entity2;
    Entity* targetEntity = EM.GetEntity(entity1);
    PositionComponent* position;
    Application::Application()
    {
        logger.Log(Engine::LogLevel::Debug, "Logger Initialized.");
        // Create a window and set its event callback
        m_Window = std::unique_ptr<Window>(Window::Create());
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        std::unique_ptr<Component> positionComponent = std::make_unique<PositionComponent>();
        targetEntity->AddComponent(std::move(positionComponent));
        position = dynamic_cast<PositionComponent*>(targetEntity->GetComponent(ComponentType::Position));
    }   

    Application::~Application()
    {
        // Destructor
    }

    void Application::OnEvent(Event& e)
    {
        // Event handler
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        logger.Log(Engine::LogLevel::Event, e.ToString());
    }

    void Application::Run()
    {
        logger.Log(Engine::LogLevel::App, "Application Running.");
        Application::InitializeGLEW();
        logger.Log(Engine::LogLevel::App, "Scene Setup");

        while (m_Running)
        {

            m_Window->OnUpdate();
            
            UpdateDeltaTime();
            UpdateWindowTitle();

            if (Input::IsKeyPressed(GLFW_KEY_1))
            {
                // Clone entity1 and store its ID
                entity2 = EM.CloneEntity(entity1);
                targetEntity = EM.GetEntity(entity2);
            }

            std::cout << "EntityID: " << static_cast<int>(targetEntity->id) << std::endl;
            //std::cout << "PositionComponent X: " << position->x << " Y: " << position->y << std::endl;
            std::cout << "Number of entities: " << EM.entities.size() << std::endl;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        // Handle window close event
        m_Running = false;
        return true;
    }

    void Application::UpdateDeltaTime()
    {
        static int frameCount = 0;
        // Calculate delta time (time between frames)
        double currentTime = glfwGetTime();
        dt = currentTime - previousTime;
        frameCount++;
        if (dt >= 1.0)
        {
            // Calculate frames per second (FPS)
            fps = double(frameCount) / dt;
            frameCount = 0;
            previousTime = currentTime;
        }
    }

    void Application::UpdateWindowTitle() 
    {
        // Update the window title with FPS
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << fps;
        std::string fps_str = ss.str();
        std::string title_str = "Game2 | FPS: " + fps_str;
        glfwSetWindowTitle(glfwGetCurrentContext(), title_str.c_str());
    }

    void Application::SetupScene() {
        // Set up the vertex positions and indices
        float positions[] = {
            -50.0f, -50.0f, 0.0f, 0.0f,    // 0
            50.0f, -50.0f, 1.0f, 0.0f,      // 1
            50.0f, 50.0f, 1.0f, 1.0f,       // 2
            -50.0f, 50.0f, 0.0f, 1.0f      // 3
        };

        unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
        };

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

        VertexArray va = VertexArray();
        VertexBuffer vb(positions, 4 * 4 * sizeof(float));

        VertexBufferLayout layout{};
        layout.Push<float>(2);
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        IndexBuffer ib(indices, 6);

        // Moving of the texture
        glm::mat4 proj = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f);
        glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));    // Left translation

        Shader shader("Shaders/Basic.shader");
        shader.Bind();
        shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        Texture luffyTexture("Resource/texture/Luffy.png");
        luffyTexture.Bind();
        shader.SetUniform1i("u_Texture", 0);

        Texture zoroTexture("res/textures/zoro.png"); // Load the new texture
        zoroTexture.Bind(1); // Bind the texture to a different texture unit (e.g., unit 1)

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();
    }

    void Application::InitializeGLEW() {
        if (glewInit() != GLEW_OK) {
            std::cerr << "Failed to initialize GLEW" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        std::cout << glGetString(GL_VERSION) << std::endl;
    }
}
