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
#include "AssetManager.h"
#include "Pathfinding.h"

// Global variables for frames per second (fps) calculation
double fps = 0.00;
double previousTime = glfwGetTime();  // Previous time for FPS calculation
double loopTime = 0.0;  // Definition of loopTime
double dt = 0.0;

// Variable for last key pressed
int lastKeyPressed = 0;

// Variable for getting the path of the pathfinding
std::vector<std::pair<int, int>> path;

namespace Engine
{
    // Audio file paths and SoundInfo objects
    AudioEngine audioEngine;
    SoundInfo sound("Resource/Audio/mainmenu_song.wav", "01");
    SoundInfo sound2("Resource/Audio/levelwin.wav", "02");
    Engine::Input InputHandler;
    // Window Properties configuration loaded from a file
    std::shared_ptr<Loader> loader = nullptr;
    Engine::WindowConfig windowProps = loader->LoadWindowPropsFromConfig("Resource/Config/config.txt");
    std::shared_ptr<ImGuiWrapper> m_ImGuiWrapper = nullptr;
    std::shared_ptr<SystemsManager> systemsManager = nullptr;

    // Entity-related instances and properties
    GraphicsSystem graphicsSystem;
    std::shared_ptr<EntityManager> EM;
    Engine::PrefabManager PM;
    EntityID cloneEntity;
    Entity* targetEntity;
    TransformComponent* transformTest;
    CollisionComponent* collisionTest;
    PhysicsComponent* physicsTest;
    ComponentFactory CF;

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
            Logger::GetInstance().Log(Engine::LogLevel::Error, "Failed to initialize GLFW");
            return; // Handle the initialization error
        }

        // Create the window
        m_Window = std::unique_ptr<Window>(Window::Create(windowProps));
        if (!m_Window) {
            Logger::GetInstance().Log(Engine::LogLevel::Error, "Failed to create the Window");
            return; // Handle the window creation error
        }

        // Set event callback
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        // Systems Manager & Asset Manager Initialization
        assetManager = std::make_shared<Engine::AssetManager>();
        for (int i = 0; i < TextureClassCount; i++) {
            assetManager->loadTexture(i, assetManager->textureFilePaths.at(i));
        }

        EM = std::make_shared<Engine::EntityManager>();

        systemsManager = std::make_shared<SystemsManager>(assetManager, EM);
        systemsManager->Initialize();

        // Load scene from a file
        loader = std::make_unique<Engine::Loader>(EM, &PM);
        Logger::GetInstance().Log(LogLevel::Debug, "Loading Scene");
        loader->LoadScene("Resource/Scenes/testscene.txt");
        Logger::GetInstance().Log(LogLevel::Debug, "Scene Loaded");
        Logger::GetInstance().Log(LogLevel::Debug, "Loading Prefabs");
        loader->LoadPrefabs("Resource/Prefabs.txt");
        Logger::GetInstance().Log(LogLevel::Debug, "Prefabs Loaded");
        
        if (EM->GetEntity(1) != nullptr) {
            targetEntity = EM->GetEntity(1);
            transformTest = dynamic_cast<TransformComponent*>(targetEntity->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
            collisionTest = dynamic_cast<CollisionComponent*>(targetEntity->GetComponent(ComponentType::Collision));
            physicsTest = dynamic_cast<PhysicsComponent*>(targetEntity->GetComponent(ComponentType::Physics));
        }
        else
            targetEntity = EM->GetEntity(0);
        // Initialize audio files and load sounds
        audioEngine.init();
        audioEngine.loadSound(sound);
        audioEngine.loadSound(sound2);
        sound.setLoop();
        sound2.setLoop();

        // Initialize ImGuiWrapper
        m_ImGuiWrapper = std::make_unique<Engine::ImGuiWrapper>(EM, &PM, assetManager);
        m_ImGuiWrapper->Initialize();
        m_ImGuiWrapper->OnAttach();
        m_ImGuiWrapper->SetTargetEntity(targetEntity);

        // Initializing pathfinding
        int startX = 0;
        int startY = 0;
        int goalX = 200;
        int goalY = 200;

        Pathfinding pathfinder(720, 1280); // Create an instance of the Pathfinding class

        pathfinder.setStart(startX, startY); // Set the start position
        pathfinder.setGoal(goalX, goalY); // Set the goal position

        path = pathfinder.findShortestPath(); // Use the Pathfinding class to find the path

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
        Logger::GetInstance().Log(Engine::LogLevel::App, "Application Running.");

        while (m_Running)
        {
            auto loopStartTime = std::chrono::high_resolution_clock::now();
            // Update input, window, delta time, and window title
            InputHandler.Update();
            m_Window->OnUpdate();
            Application::UpdateDeltaTime();
            Application::UpdateWindowTitle();

            // Audio handling based on key input
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

            //Systems State Toggle Test
            if (InputHandler.IsKeyTriggered(KEY_1))
            {
                systemsManager->ToggleSystemState<CollisionSystem>();
            }

            if (InputHandler.IsKeyTriggered(KEY_2))
            {
                systemsManager->ToggleSystemState<PhysicsSystem>();
            }    

            if (m_ImGuiWrapper->TargetEntityGetter())
            {
                if (m_ImGuiWrapper->TargetEntityGetter()->HasComponent(ComponentType::Transform)) {
                    transformTest = dynamic_cast<TransformComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
                }
                if (m_ImGuiWrapper->TargetEntityGetter()->HasComponent(ComponentType::Collision)) {
                    collisionTest = dynamic_cast<CollisionComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Collision));
                }
                if (m_ImGuiWrapper->TargetEntityGetter()->HasComponent(ComponentType::Physics)) {
                    physicsTest = dynamic_cast<PhysicsComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Physics));
                }
            }
                    
            // Define a threshold for the minimum and maximum scales
            const float minScale = 0.5f; // Adjust this value as needed
            const float maxScale = 2.0f; // Adjust this value as needed

            // Add a flag to keep track of scaling direction
            bool scalingUp = false;
            bool scalingDown = false;

            // Variables for last position
            float lastPositionX = transformTest->position.x;
            float lastPositionY = transformTest->position.y;
            float nextPositionX = lastPositionX + 1;
            float nextPositionY = lastPositionY + 1;

            if (physicsTest && transformTest) //INPUT TESTING FOR UNIT ENTITIES
            {
                if (path.empty()) {
                    std::cout << "No path found!" << std::endl;
                }
                else {
                    // If a path is found, move the unit towards the next position in the path
                    std::pair<int, int> nextPosition = path[0]; // Get the next position

                    // Debugging
                    std::cout << nextPosition.first << std::endl;
                    std::cout << nextPosition.second << std::endl;

                    // Update the unit's position
                    transformTest->position.x = nextPosition.first;
                    transformTest->position.y = nextPosition.second;
                    

                    // Remove the first position from the path to move to the next one in the next frame
                    path.erase(path.begin());
                }

                if (collisionTest->isColliding) {
                    if (lastKeyPressed == 1 || (lastPositionY < nextPositionY)) {
                        transformTest->position.y = lastPositionY - 10.f;
                    }
                    if (lastKeyPressed == 2 || (lastPositionY > nextPositionY)) {
                        transformTest->position.y = lastPositionY + 10.f;
                    }
                    if (lastKeyPressed == 3 || (lastPositionX < nextPositionX)) {
                        transformTest->position.x = lastPositionX + 10.f;
                    }
                    if (lastKeyPressed == 4 || (lastPositionX > nextPositionX)) {
                        transformTest->position.x = lastPositionX - 10.f;
                    }
                }

                if (InputHandler.IsKeyPressed(KEY_UP) && !(collisionTest->isColliding))
                {
                    lastPositionY += transformation;
                    transformTest->position.y = lastPositionY;
                    if (physicsTest->velocity.y <= 0.0f) {
                        physicsTest->velocity.y = 1.0f;
                    }
                    lastKeyPressed = 1;
                }

                else if (InputHandler.IsKeyPressed(KEY_DOWN) && !(collisionTest->isColliding))
                {
                    lastPositionY -= transformation;
                    transformTest->position.y = lastPositionY;
                    if (physicsTest->velocity.y >= -0.0f) {
                        physicsTest->velocity.y = -1.0f;
                    }
                    lastKeyPressed = 2;
                }

                else if (InputHandler.IsKeyPressed(KEY_LEFT) && !(collisionTest->isColliding))
                {
                    lastPositionX -= transformation;
                    transformTest->position.x = lastPositionX;
                    if (physicsTest->velocity.x >= -0.0f) {
                        physicsTest->velocity.x = -1.0f;
                    }
                    lastKeyPressed = 3;
                }

                else if (InputHandler.IsKeyPressed(KEY_RIGHT) && !(collisionTest->isColliding))
                {
                    lastPositionX += transformation;
                    transformTest->position.x = lastPositionX;
                    if (physicsTest->velocity.x <= 0.0f) {
                        physicsTest->velocity.x = 1.0f;
                    }
                    lastKeyPressed = 4;
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
                    physicsTest->velocity.x = 0.0f;
                    physicsTest->velocity.y = 0.0f;
                }

            }


            //System Updating
            systemsManager->UpdateSystems(EM->GetEntities());

            //Entity Debug
            //std::cout << "EntityID: " << static_cast<int>(targetEntity->id) << " Number of Components: " << targetEntity->components.size() << std::endl;
            //std::cout << "Number of entities: " << EM.entities.size() << std::endl;
            auto loopEndTime = std::chrono::high_resolution_clock::now();
            loopTime = std::chrono::duration_cast<std::chrono::microseconds>(loopEndTime - loopStartTime).count() / 1000.0; // Convert to milliseconds

            m_ImGuiWrapper->OnUpdate();
            systemsManager->ResetSystemTimers();


            if (InputHandler.IsKeyTriggered(KEY_ESCAPE))
                m_Running = false;

            // Reset system timers for the next loop iteration
            if (InputHandler.IsKeyTriggered(KEY_F12)) // Use any key you like, for this example I'm using 'C'
            {
                int* crashPointer = nullptr;
                *crashPointer = 42; // This will cause a read access violation, simulating a crash
            }
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
        loader->SavePrefabs("Resource/Prefabs.txt");
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
