#include "pch.h"

#include <GLFW/glfw3.h>
#include "Application.h"
#include "Input.h"
#include "EntityManager.h"
#include "PositionComponent.h"
#include "Entity.h"
#include "System.h"

// Global variables
double fps = 0.00;  // Frames per second
double previousTime = glfwGetTime();  // Previous time for FPS calculation
int frameCount = 0;  // Frame count for FPS calculation
double delta = 0.0;  // Time difference between frames (delta time)

namespace Engine
{
    // Create a logger instance
    Engine::Logger logger;
    Engine::EntityManager EM;
    EntityID entity1 = EM.CreateEntity();
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

        while (m_Running)
        {
            m_Window->OnUpdate();
            
            // Calculate delta time (time between frames)
            double currentTime = glfwGetTime();
            delta = currentTime - previousTime;
            frameCount++;

            if (delta >= 1.0)
            {
                // Calculate frames per second (FPS)
                fps = double(frameCount) / delta;
                frameCount = 0;
                previousTime = currentTime;
            }

            if (Input::IsKeyPressed(GLFW_KEY_1))
            {
                // Clone entity1 and store its ID
                EM.CloneEntity(entity1);
            }
            
            std::cout << "EntityID: " << targetEntity->id << std::endl;
            std::cout << "PositionComponent X: " << position->x << " Y: " << position->y << std::endl;
            std::cout << "Number of entities: " << EM.entities.size() << std::endl;
            // Update the window title with FPS
            std::stringstream ss;
            ss << std::fixed << std::setprecision(2) << fps;
            std::string fps_str = ss.str();
            std::string title_str = "Game2 | FPS: " + fps_str;
            glfwSetWindowTitle(glfwGetCurrentContext(), title_str.c_str());
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        // Handle window close event
        m_Running = false;
        return true;
    }
}
