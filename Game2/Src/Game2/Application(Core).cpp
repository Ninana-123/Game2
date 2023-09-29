#include "pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Application.h"
#include "Input.h"
#include "EntityManager.h"
#include "SystemsManager.h"
#include "ComponentFactory.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "System.h"
#include "KeyCodes.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "ImGuiWrapper.h"
#include "AudioEngine.h"
#include "Loader.h"

double fps = 0.00;  // Frames per second
double previousTime = glfwGetTime();  // Previous time for FPS calculation
extern double dt = 0.0;  // Time difference between frames (delta time)

namespace Engine
{
    std::unique_ptr<Loader> loader;
    //Window Properties
    Engine::WindowProps windowProps = loader->LoadWindowPropsFromConfig("config.txt");

    //Set filepath of audio to the variable
    AudioEngine audioEngine;
    SoundInfo sound("Resource/Audio/mainmenu_song.wav", "01");
    SoundInfo sound2("Resource/Audio/levelwin.wav", "02");

    // Create a logger instance
    Engine::Logger logger;
    Engine::Input InputHandler;
    GraphicsSystem graphicsSystem;
    std::unique_ptr<ImGuiWrapper> m_ImGuiWrapper;

    //Entity instances
    Engine::EntityManager EM;
    Engine::SystemsManager SM;
    EntityID cloneEntity;
    Entity* targetEntity;
    TransformComponent* transformTest;
    CollisionComponent* collisionTest;
    PhysicsComponent* physicsTest;
    ComponentFactory CF;

    float vx = 0.0f;
    float vy = 0.0f;
    float scalar = 0.5f;
    float rotation = 0.125f;
    int transformation = 5;
    bool currentlyPlayingSound = 0;

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
        m_Window = std::unique_ptr<Window>(Window::Create(windowProps));
        if (!m_Window) {
            logger.Log(Engine::LogLevel::Error, "Failed to create the Window");
            return; // Handle the window creation error
        }

        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        //Systems Manager Initialization
        //Currently initializes TestSystem and Graphics
        SM.Initialize();

        loader = std::make_unique<Engine::Loader>(&EM);
        logger.Log(LogLevel::Debug, "Loading Scene");
        loader->LoadScene("testscene.txt");
        logger.Log(LogLevel::Debug, "Scene Loaded");
        targetEntity = EM.GetEntity(0);
        transformTest = dynamic_cast<TransformComponent*>(targetEntity->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
        collisionTest = dynamic_cast<CollisionComponent*>(targetEntity->GetComponent(ComponentType::Collision));
        physicsTest = dynamic_cast<PhysicsComponent*>(targetEntity->GetComponent(ComponentType::Physics));

        //initialize audio files
        audioEngine.init();
        //load both audio 
        audioEngine.loadSound(sound);
        audioEngine.loadSound(sound2);
        sound.setLoop();
        sound2.setLoop();

        m_ImGuiWrapper = std::make_unique<Engine::ImGuiWrapper>(&EM);
        m_ImGuiWrapper->OnAttach();
        m_ImGuiWrapper->SetTargetEntity(targetEntity);
    }

    void Application::OnEvent(Event& e)
    {
        // Event handler
        EventDispatcher dispatcher(e);
       dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
       //logger.Log(Engine::LogLevel::Event, e.ToString());
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

            if (currentlyPlayingSound == false) {
                if (InputHandler.IsKeyTriggered(KEY_9)) {
                    audioEngine.playSound(sound);
                    currentlyPlayingSound = true;
                }
            }

            if (currentlyPlayingSound == false) {
                if (InputHandler.IsKeyTriggered(KEY_0)) {
                    audioEngine.playSound(sound2);
                    currentlyPlayingSound = true;
                }
            }

            if (InputHandler.IsKeyTriggered(KEY_8) && audioEngine.soundIsPlaying(sound)) {
                audioEngine.stopSound(sound);
                currentlyPlayingSound = false;
            }

            if (InputHandler.IsKeyTriggered(KEY_7) && audioEngine.soundIsPlaying(sound2)) {
                audioEngine.stopSound(sound2);
                currentlyPlayingSound = false;
            }

            if (InputHandler.IsKeyTriggered(KEY_1))
            {
                SM.ToggleSystemState<CollisionSystem>();
            }

            if (InputHandler.IsKeyTriggered(KEY_2))
            {
                SM.ToggleSystemState<PhysicsSystem>();
            }          

            transformTest = dynamic_cast<TransformComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
            collisionTest = dynamic_cast<CollisionComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Collision));
            physicsTest= dynamic_cast<PhysicsComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Physics));

            if (physicsTest && transformTest)
            {
                if (InputHandler.IsKeyPressed(KEY_UP))
                {
                    //transformTest->y += transformation;
                    physicsTest->velocityY += 10.0f;
                }

                if (InputHandler.IsKeyPressed(KEY_DOWN))
                {
                    //transformTest->y -= transformation;
                    physicsTest->velocityY -= 10.0f;
                }

                if (InputHandler.IsKeyPressed(KEY_LEFT))
                {
                    //transformTest->x -= transformation;
                    physicsTest->velocityX -= 10.0f;
                }

                if (InputHandler.IsKeyPressed(KEY_RIGHT))
                {
                    //transformTest->x += transformation;
                    physicsTest->velocityX += 10.0f;
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

            }

            //System Updating
            SM.UpdateSystems(EM.GetEntities());

            //Entity Debug
            //std::cout << "EntityID: " << static_cast<int>(targetEntity->id) << " Number of Components: " << targetEntity->components.size() << std::endl;
            //std::cout << "vel X: " << physicsTest->velocityX << " Y: " << physicsTest->velocityY << std::endl;
            //std::cout << "Number of entities: " << EM.entities.size() << std::endl;
            m_ImGuiWrapper->OnUpdate();

        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        UNREFERENCED_PARAMETER(e);
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
        std::string title_str = windowProps.Title +" | FPS: " + fps_str;
        glfwSetWindowTitle(glfwGetCurrentContext(), title_str.c_str());
    }
    

}
