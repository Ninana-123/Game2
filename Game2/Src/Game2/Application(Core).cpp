/******************************************************************************/
/*!
\file		Application.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		This file contains the implementation of the main application class
            and its functionalities, including window initialization, event 
            handling, audio, graphics systems, and entity management.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
//Includes
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


// Global variables for frames per second (fps) calculation
double fps = 0.00;
double previousTime = glfwGetTime();  // Previous time for FPS calculation
extern double dt = 0.0;  // Time difference between frames (delta time)

namespace Engine
{
    std::unique_ptr<Loader> loader;
    // Window Properties configuration loaded from a file
    Engine::WindowConfig windowProps = loader->LoadWindowPropsFromConfig("config.txt");

    // Audio file paths and SoundInfo objects
    AudioEngine audioEngine;
    SoundInfo sound_BGM("Resource/Audio/mainmenu_song.wav", "01");
    SoundInfo sound_Win("Resource/Audio/levelwin.wav", "02");
    SoundInfo sound_Arrow("Resource/Audio/archer_shoot.wav", "03");
    SoundInfo sound_Slash("Resource/Audio/samurai_slash.wav", "04");

    Engine::Logger logger;
    Engine::Input InputHandler;
    GraphicsSystem graphicsSystem;
    std::unique_ptr<ImGuiWrapper> m_ImGuiWrapper;

    // Entity-related instances and properties
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
    float scalar = 0.1f;
    float rotation = 0.125f;
    int transformation = 5;

    // Flag to track if a sound is currently playing
    bool currentlyPlayingSound = 0;
    /*!**********************************************************************
    \brief
    Constructor for the Application class
    *************************************************************************/
    Application::Application()
    {
    }   
    /*!**********************************************************************
    \brief
    Destructor for the Application class
    *************************************************************************/
    Application::~Application()
    {
    }
    /*!**********************************************************************
    \brief
    Initialize the application
    This function initializes various components and systems needed 
    for the application to run.
    *************************************************************************/
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

        // Set event callback
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        // Systems Manager Initialization: initializes TestSystem and Graphics
        SM.Initialize();

        // Load scene from a file
        loader = std::make_unique<Engine::Loader>(&EM);
        logger.Log(LogLevel::Debug, "Loading Scene");
        loader->LoadScene("testscene.txt");
        logger.Log(LogLevel::Debug, "Scene Loaded");
        targetEntity = EM.GetEntity(1);
        transformTest = dynamic_cast<TransformComponent*>(targetEntity->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
        collisionTest = dynamic_cast<CollisionComponent*>(targetEntity->GetComponent(ComponentType::Collision));
        physicsTest = dynamic_cast<PhysicsComponent*>(targetEntity->GetComponent(ComponentType::Physics));

        // Initialize audio files and load sounds
        audioEngine.init();
        audioEngine.loadSound(sound_BGM);
        audioEngine.loadSound(sound_Win);
        audioEngine.loadSound(sound_Arrow);
        audioEngine.loadSound(sound_Slash);
        sound_BGM.setLoop();
        sound_Win.setLoop();
        sound_Arrow.setLoop();
        sound_Slash.setLoop();

        // Initialize ImGuiWrapper
        m_ImGuiWrapper = std::make_unique<Engine::ImGuiWrapper>(&EM);
        m_ImGuiWrapper->OnAttach();
        m_ImGuiWrapper->SetTargetEntity(targetEntity);
    }
    /*!**********************************************************************
    \brief
    Event handler for processing events
    This function handles incoming events and dispatches them accordingly.
    *************************************************************************/
    void Application::OnEvent(Event& e)
    {
        // Event handler
        EventDispatcher dispatcher(e);
       dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
       //logger.Log(Engine::LogLevel::Event, e.ToString());
       m_ImGuiWrapper->OnEvent(e);
    }

    /*!**********************************************************************
    \brief
    Run the application
    This function runs the main loop of the application, handling input,
    updating systems, and rendering.
    *************************************************************************/
    void Application::Run()
    {
        logger.Log(Engine::LogLevel::App, "Application Running.");

        audioEngine.playSound(sound_BGM);

        while (m_Running)
        {
            // Update input, window, delta time, and window title
            InputHandler.Update();
            m_Window->OnUpdate();
            Application::UpdateDeltaTime();
            Application::UpdateWindowTitle();

            // Audio handling based on key input
            if (currentlyPlayingSound == false) {
                if (InputHandler.IsKeyTriggered(KEY_3)) {
                    audioEngine.playSound(sound_Win);
                    currentlyPlayingSound = true;
                }
            }

            if (currentlyPlayingSound == false) {
                if (InputHandler.IsKeyTriggered(KEY_5)) {
                    audioEngine.playSound(sound_Arrow);
                    currentlyPlayingSound = true;
                }
            }

            if (currentlyPlayingSound == false) {
                if (InputHandler.IsKeyTriggered(KEY_7)) {
                    audioEngine.playSound(sound_Slash);
                    currentlyPlayingSound = true;
                }
            }

            if (InputHandler.IsKeyTriggered(KEY_9) && audioEngine.soundIsPlaying(sound_BGM)) {
                audioEngine.stopSound(sound_BGM);
                currentlyPlayingSound = false;
            }

            if (InputHandler.IsKeyTriggered(KEY_4) && audioEngine.soundIsPlaying(sound_Win)) {
                audioEngine.stopSound(sound_Win);
                currentlyPlayingSound = false;
            }

            if (InputHandler.IsKeyTriggered(KEY_6) && audioEngine.soundIsPlaying(sound_Arrow)) {
                audioEngine.stopSound(sound_Arrow);
                currentlyPlayingSound = false;
            }

            if (InputHandler.IsKeyTriggered(KEY_8) && audioEngine.soundIsPlaying(sound_Slash)) {
                audioEngine.stopSound(sound_Slash);
                currentlyPlayingSound = false;
            }

            //Systems State Toggle Test
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
            physicsTest = dynamic_cast<PhysicsComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Physics));
            
            // Define a threshold for the minimum and maximum scales
            const float minScale = 0.5f; // Adjust this value as needed
            const float maxScale = 2.0f; // Adjust this value as needed

            // Add a flag to keep track of scaling direction
            bool scalingUp = false;
            bool scalingDown = false;
            if (physicsTest && transformTest) //INPUT TESTING FOR UNIT ENTITIES
            {
                if (InputHandler.IsKeyPressed(KEY_UP))
                {
                    transformTest->y += transformation;
                    //physicsTest->velocityY = 10.0f;
                }
                else if (InputHandler.IsKeyPressed(KEY_DOWN))
                {
                    transformTest->y -= transformation;
                    //physicsTest->velocityY = -10.0f;
                }
                else if (InputHandler.IsKeyPressed(KEY_LEFT))
                {
                    transformTest->x -= transformation;
                    //physicsTest->velocityX = -10.0f;
                }
                else if (InputHandler.IsKeyPressed(KEY_RIGHT))
                {
                    transformTest->x += transformation;
                    //physicsTest->velocityX = 10.0f;
                }
                else if (InputHandler.IsKeyPressed(KEY_R))
                {
                    transformTest->rot += rotation; //Rotate counterclockwise
                }
                else if (InputHandler.IsKeyPressed(KEY_T))
                {
                    transformTest->rot -= rotation; //Rotate counterclockwise
                }
                else if (InputHandler.IsKeyPressed(KEY_Z))
                {
                    // Scale Up
                    transformTest->scaleX += scalar;
                    transformTest->scaleY += scalar;

                    // Check if the scale exceeds the maximum limit
                    if (transformTest->scaleX > maxScale)
                    {
                        transformTest->scaleX = maxScale;
                        transformTest->scaleY = maxScale;
                        scalingUp = false; // Stop scaling up
                        scalingDown = true; // Start scaling down
                    }
                    else
                    {
                        scalingUp = true; // Continue scaling up
                        scalingDown = false; // Stop scaling down
                    }
                }
                else if (InputHandler.IsKeyPressed(KEY_X))
                {
                    // Scale Down
                    transformTest->scaleX -= scalar;
                    transformTest->scaleY -= scalar;

                    // Check if the scale falls below the minimum limit
                    if (transformTest->scaleX < minScale)
                    {
                        transformTest->scaleX = minScale;
                        transformTest->scaleY = minScale;
                        scalingUp = true; // Start scaling up
                        scalingDown = false; // Stop scaling down
                    }
                    else
                    {
                        scalingUp = false; // Stop scaling up
                        scalingDown = true; // Continue scaling down
                    }
                }
                else
                {
                    physicsTest->velocityX = 0.0f;
                    physicsTest->velocityY = 0.0f;
                }

            }

            audioEngine.update();

            //System Updating
            SM.UpdateSystems(EM.GetEntities());

            //Entity Debug
            //std::cout << "EntityID: " << static_cast<int>(targetEntity->id) << " Number of Components: " << targetEntity->components.size() << std::endl;
            //std::cout << "Number of entities: " << EM.entities.size() << std::endl;
            m_ImGuiWrapper->OnUpdate();

        }
    }
    /*!**********************************************************************
    \brief
    Handles the window close event.
    This function handles the event triggered when the application's
    window is closed.
    \param[in] e 
    WindowCloseEvent object containing event information.
    \return
    True if the window close event was handled successfully, false otherwise.
    *************************************************************************/
    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        UNREFERENCED_PARAMETER(e);
        // Handle window close event
        m_Running = false;
        return true;
    }
    /*!**********************************************************************
    \brief
    Handles the window resize event.
    This function handles the event triggered when the application's
    window is resized.
    \param[in] e
    WindowResizeEvent object containing event information.
    *************************************************************************/
    void Application::OnWindowResize(WindowResizeEvent& e)
    {
        // Update the viewport and projection matrix
        graphicsSystem.UpdateViewport(e.GetWidth(), e.GetHeight());
    }
    /*!**********************************************************************
    \brief
    Updates the delta time and calculates frames per second (FPS).
    *************************************************************************/
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
    /*!**********************************************************************
    \brief
    Updates the window title to display FPS.
    *************************************************************************/
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
