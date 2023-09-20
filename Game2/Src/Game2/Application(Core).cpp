#include "pch.h"

#include "Graphics.h"
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


namespace Engine
{
    // Create a logger instance
    Engine::Logger logger;

    //Entity instances
    Engine::EntityManager EM;
    EntityID entity1, entity2;
    Entity* targetEntity;
    PositionComponent* position;

    Application::Application()
    {
        logger.Log(Engine::LogLevel::Debug, "Logger Initialized.");
        // Create a window and set its event callback
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
            logger.Log(Engine::LogLevel::Error, "Failed to create the window");
            return; // Handle the window creation error
        }

        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        //Entity creation
        entity1 = EM.CreateEntity();
        targetEntity = EM.GetEntity(entity1);
        //add component to entity
        std::unique_ptr<Component> positionComponent = std::make_unique<PositionComponent>();
        targetEntity->AddComponent(std::move(positionComponent));
        position = dynamic_cast<PositionComponent*>(targetEntity->GetComponent(ComponentType::Position)); //reference to Entity Position data
        
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

        while (m_Running)
        {

            m_Window->OnUpdate();
            
            Application::UpdateDeltaTime();
            Application::UpdateWindowTitle();
            if (Input::IsKeyPressed(GLFW_KEY_1))
            {
                // Clone entity1 and store its ID
                entity2 = EM.CloneEntity(entity1);
                targetEntity = EM.GetEntity(entity2);
            }
            /*
            std::cout << "EntityID: " << static_cast<int>(targetEntity->id) << " Number of Components: " << targetEntity->components.size() << std::endl;
            //std::cout << "PositionComponent X: " << position->x << " Y: " << position->y << std::endl;
            std::cout << "Number of entities: " << EM.entities.size() << std::endl;
            */
         
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
    

}
