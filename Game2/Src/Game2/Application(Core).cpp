#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Input.h"
#include "EntityManager.h"
#include "SystemsManager.h"
#include "ComponentFactory.h"
#include "PositionComponent.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "System.h"
#include "KeyCodes.h"
#include "Graphics.h"
#include "ImGuiWrapper.h"

double fps = 0.00;  // Frames per second
double previousTime = glfwGetTime();  // Previous time for FPS calculation
double dt = 0.0;  // Time difference between frames (delta time)


namespace Engine
{
    // Create a logger instance
    Engine::Logger logger;
    Engine::Input InputHandler;
    Graphics graphicsSystem;
    std::unique_ptr<ImGuiWrapper> m_ImGuiWrapper;

    //Entity instances
    Engine::EntityManager EM;
    Engine::SystemsManager SM;
    EntityID entity1, entity2;
    Entity* targetEntity;
    TransformComponent* transformTest;
    ComponentFactory CF;

    float scalar = 0.5f;
    float rotation = 0.125f;
    float transformation = 5.0f;

    Application::Application()
    {
        logger.Log(Engine::LogLevel::Debug, "Logger Initialized.");
    }   

    Application::~Application()
    {
        // Destructor
    }

    void Application::Initialize()
    {
       
        // Initialize GLFW
        if (!glfwInit()) {
            logger.Log(Engine::LogLevel::Error, "Failed to initialize GLFW");
            return; // Handle the initialization error
        }

        // Create the window
        m_Window = std::unique_ptr<Window>(Window::Create());
        if (!m_Window) {
            logger.Log(Engine::LogLevel::Error, "Failed to create the Window");
            return; // Handle the window creation error
        }

        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        //Systems Manager Initialization
        //Currently initializes TestSystem and Graphics
        SM.Initialize();

        m_ImGuiWrapper = std::make_unique<Engine::ImGuiWrapper>();
        m_ImGuiWrapper->OnAttach();

        //Entity creation
        entity1 = EM.CreateEntity();
        targetEntity = EM.GetEntity(entity1);

        //add component to entity
        targetEntity->AddNewComponent(ComponentType::Transform);
        targetEntity->AddNewComponent(ComponentType::Position);
        transformTest = dynamic_cast<TransformComponent*>(targetEntity->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
      
    }

    void Application::OnEvent(Event& e)
    {
        // Event handler
        EventDispatcher dispatcher(e);
       dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
       logger.Log(Engine::LogLevel::Event, e.ToString());
       m_ImGuiWrapper->OnEvent(e);
    }

    void Application::Run()
    {
        logger.Log(Engine::LogLevel::App, "Application Running.");
            

        while (m_Running)
        {
            InputHandler.Update();
            m_Window->OnUpdate();
            Application::UpdateDeltaTime();
            Application::UpdateWindowTitle();

            
            if (InputHandler.IsKeyTriggered(KEY_1))
            {
                // Clone entity1 and store its ID
                entity2 = EM.CloneEntity(entity1);
                targetEntity = EM.GetEntity(entity2);
            }
            
            if (InputHandler.IsKeyPressed(KEY_UP))
            {
                transformTest->y += transformation;
            }
            
            if (InputHandler.IsKeyPressed(KEY_DOWN))
            {
                transformTest->y -= transformation;
            }

            if (InputHandler.IsKeyPressed(KEY_LEFT))
            {
                transformTest->x -= transformation;
            }

            if (InputHandler.IsKeyPressed(KEY_RIGHT))
            {
                transformTest->x += transformation;
            }

            if (InputHandler.IsKeyPressed(KEY_R))
            {
                transformTest->rot += rotation; //Rotate counterclockwise
            };

            if (InputHandler.IsKeyPressed(KEY_T))
            {
                transformTest->rot -= rotation; //Rotate counterclockwise
            };

            if (InputHandler.IsKeyPressed(KEY_Z))
            {
                //Scale Up
                transformTest->scaleX += scalar; 
                transformTest->scaleY += scalar; 
            }

            if (InputHandler.IsKeyPressed(KEY_X))
            {
                // Scale Down
                transformTest->scaleX -= scalar; 
                transformTest->scaleY -= scalar; 
            }


            //System Updating
            SM.UpdateSystems(EM.GetEntities());

            //Entity Debug
            
            std::cout << "EntityID: " << static_cast<int>(targetEntity->id) << " Number of Components: " << targetEntity->components.size() << std::endl;
            std::cout << "TransformComponent X: " << transformTest->x << " Y: " << transformTest->y << std::endl;
            std::cout << "Number of entities: " << EM.entities.size() << std::endl;
            
            m_ImGuiWrapper->OnUpdate();

        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        // Handle window close event
        m_Running = false;
        return true;
    }

    void Application::OnWindowResize(WindowResizeEvent& e)
    {
        // Update the viewport and projection matrix
        graphicsSystem.UpdateViewport(e.GetWidth(), e.GetHeight());
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
    

}
