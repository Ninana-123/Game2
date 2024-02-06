/******************************************************************************/
/*!
\file		Application.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\co         Wayne Kwok Jun Lin
\co         email: k.junlinwayne@digipen.edu
\date   	29/09/2923
\brief		This file contains the implementation of the main application class
            and its functionalities, including window initialization, event 
            handling, audio, graphics systems, and entity management.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#include "pch.h"
#include "Application.h"
#include "Input.h"
#include "EntityManager.h"
#include "SystemsManager.h"
#include "ComponentFactory.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "System.h"
#include "KeyCodes.h"
#include "ImGuiWrapper.h"
#include "AudioEngine.h"
#include "Loader.h"
#include "AssetManager.h"
#include "inGameGUI.h"
#include "CollisionSystem.h"
#include "WindowsWindow.h"
#include "Input.h"
#include "MainMenu.h"

// Global variables for frames per second (fps) calculation
double fps = 0.00;
auto previousTime = std::chrono::high_resolution_clock::now();;  // Previous time for FPS calculation
double loopTime = 0.0;  // Definition of loopTime
const double fixedDeltaTime = 1.0 / 60.0;//user defined 
double accumulatedTime = 0.0;//one time definition
int currentNumberOfSteps = 0;
int e_Width = 0;
int e_Height = 0;
double prevTime = glfwGetTime();
bool isPaused = false;
bool stepOneFrame = false;
double dt = 0;
std::string initScene = "Resource/Scenes/Level0Test.txt";
//std::string nextScene = "Resource/Scenes/Level0Test.txt";

// Variable for last key pressed
int lastKeyPressed = 0;

namespace Engine
{
    // Audio file paths and SoundInfo objects
    AudioEngine audioEngine;

    Engine::Input InputHandler;
    // Window Properties configuration loaded from a file
    std::shared_ptr<Loader> loader = nullptr;
    Engine::WindowConfig windowProps = loader->LoadWindowPropsFromConfig("Resource/Config/config.txt");
    std::shared_ptr<ImGuiWrapper> m_ImGuiWrapper = nullptr;
    std::shared_ptr<SystemsManager> systemsManager = nullptr;
    std::shared_ptr<inGameGUI> m_inGameGUI = nullptr;

    // Entity-related instances and properties
    GraphicsSystem* graphicsSystem;
    CollisionSystem* collisionSystem;
    std::shared_ptr<EntityManager> EM;
    Engine::PrefabManager PM;
    EntityID cloneEntity;
    Entity* targetEntity;
    TransformComponent* transformTest;
    CollisionComponent* collisionTest;
    PhysicsComponent* physicsTest;
    ComponentFactory CF;
 
    MainMenu* mainMenu;

    float scalar = 0.1f;
    float rotation = 0.125f;
    int transformation = 5;

    // Flag to track if a sound is currently playing
    bool currentlyPlayingSound = 0;
#ifdef DEBUG
    bool isFullScreen = false;
#else
    bool isFullScreen = true;
#endif

    Application::Application()
    {
        mainMenu = new MainMenu(EM, &PM, assetManager);
    }   

    Application::~Application()
    {
        delete mainMenu;
    }

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
     
        e_Width = m_Window->GetWidth();
        e_Height = m_Window->GetHeight();

        // Set event callback
        m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

        // Systems Manager & Asset Manager Initialization
        assetManager = std::make_shared<Engine::AssetManager>();

        // Get the textureFilePaths map from the asset manager
        const auto& textureFilePaths = assetManager->GetTextureFilePaths();

        // Find the maximum mainIndex from textureFilePaths map
        int maxMainIndex = 0;
        for (const auto& entry : textureFilePaths) {
            maxMainIndex = std::max(maxMainIndex, entry.first.mainIndex);
        }

        // Load textures for each mainIndex and subIndex
        for (int mainIndex = 0; mainIndex <= maxMainIndex; ++mainIndex) {
            for (int subIndex = 0; subIndex <= 3; ++subIndex) {
                assetManager->loadTexture(mainIndex, subIndex);
            }
        }

        //Initializing Entity Manager
        EM = std::make_shared<Engine::EntityManager>();
   
        systemsManager = std::make_shared<SystemsManager>(assetManager, EM);
        systemsManager->Initialize();
        graphicsSystem = systemsManager->GetSystem<GraphicsSystem>();
        collisionSystem = systemsManager->GetSystem<CollisionSystem>();

        // Load scene from a file
        loader = std::make_unique<Engine::Loader>(EM, &PM, assetManager);
        Logger::GetInstance().Log(LogLevel::Debug, "Loading Scene");
        //loader->LoadScene(initScene);
        Logger::GetInstance().Log(LogLevel::Debug, "Scene Loaded");
        Logger::GetInstance().Log(LogLevel::Debug, "Loading Prefabs");
        loader->LoadPrefabs("Resource/Prefabs.txt");
        Logger::GetInstance().Log(LogLevel::Debug, "Prefabs Loaded");
        
        mainMenu->Initialize();

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
        //assetManager->AddAudioPath(AudioKey("sound_BGM"), "Resource/Audio/level_bgm.wav");
        //assetManager->loadAudio(AudioKey("sound_BGM"));
        //assetManager->getAudio(AudioKey("sound_BGM"))->setLoop();

        assetManager->AddAudioPath(AudioKey("sound_Win"), "Resource/Audio/levelwin.wav");
        assetManager->loadAudio(AudioKey("sound_Win"));
        assetManager->getAudio(AudioKey("sound_Win"))->setVolume(0.5f);

        assetManager->AddAudioPath(AudioKey("sound_Arrow"), "Resource/Audio/archer_shoot.wav");
        assetManager->loadAudio(AudioKey("sound_Arrow"));
        assetManager->getAudio(AudioKey("sound_Arrow"))->setVolume(0.5f);

        assetManager->AddAudioPath(AudioKey("sound_Slash"), "Resource/Audio/samurai_slash.wav");
        assetManager->loadAudio(AudioKey("sound_Slash"));
        assetManager->getAudio(AudioKey("sound_Slash"))->setVolume(0.5f);

        assetManager->AddAudioPath(AudioKey("sound_Ambience"), "Resource/Audio/forest_ambience.wav");
        assetManager->loadAudio(AudioKey("sound_Ambience"));
        assetManager->getAudio(AudioKey("sound_Ambience"))->setVolume(0.5f);

        //audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_BGM"))));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Win"))));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Arrow"))));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Slash"))));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Ambience"))));

        /*  sound_BGM.setLoop();
          sound_Win.setLoop();
          sound_Arrow.setLoop();
          sound_Slash.setLoop();*/

          // Initialize ImGuiWrapper
        m_ImGuiWrapper = std::make_unique<Engine::ImGuiWrapper>(EM, &PM, assetManager, loader);
        m_ImGuiWrapper->Initialize();
        m_ImGuiWrapper->OnAttach();
        m_ImGuiWrapper->SetTargetEntity(targetEntity);

        // Initialize inGameGUI
        m_inGameGUI = std::make_unique<Engine::inGameGUI>(EM, &PM);

        //Attaching Input Handler to EM
        InputHandler.SetEntityManager(EM);
        InputHandler.SetImGuiWrapper(m_ImGuiWrapper);
    }

    void Application::OnEvent(Event& e)
    {
        // Event handler
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&Application::OnWindowResize, this, std::placeholders::_1));
        //logger.Log(Engine::LogLevel::Event, e.ToString());
        m_ImGuiWrapper->OnEvent(e);

        if (e.GetEventType() == EventType::KeyPressed)
        {
            KeyPressedEvent& keyPressedEvent = dynamic_cast<KeyPressedEvent&>(e);

            // Check if Ctrl, Alt, and Delete keys are pressed simultaneously
            if (keyPressedEvent.GetKeyCode() == KEY_LEFT_CONTROL &&
                keyPressedEvent.GetKeyCode() == KEY_LEFT_ALT &&
                keyPressedEvent.GetKeyCode() == KEY_DELETE)
            {
                window.MinimizeWindow();
            }
        }
        if (e.GetEventType() == EventType::KeyPressed) {
            KeyPressedEvent& keyPressedEvent = dynamic_cast<KeyPressedEvent&>(e);

            // Check for ALT+ENTER (key codes may vary depending on your implementation)
            if (keyPressedEvent.GetKeyCode() == KEY_F11) {
                ToggleFullscreen();
            }
        }
    }

    void Application::ToggleFullscreen() {
        GLFWwindow* windowHandle = m_Window->GetNativeWindow(); // Obtain the native GLFW window

        if (isFullScreen) {
            // Switch to windowed mode
            glfwSetWindowMonitor(windowHandle, nullptr, 100, 100, windowProps.Width, windowProps.Height, GLFW_DONT_CARE);
        }
        else {
            // Switch to fullscreen mode
            GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
            glfwSetWindowMonitor(windowHandle, primaryMonitor, 0, 0, mode->width, mode->height, mode->refreshRate);
        }

        isFullScreen = !isFullScreen; // Toggle the state
    }

    void Application::Run()
    {
        Logger::GetInstance().Log(Engine::LogLevel::App, "Application Running.");

        //audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_BGM"))));
        audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_Ambience"))));
        previousTime = std::chrono::high_resolution_clock::now();
        /*
         if (m_ImGuiWrapper->TargetEntityGetter()->HasComponent(ComponentType::Transform)) {
             transformTest = dynamic_cast<TransformComponent*>(m_ImGuiWrapper->TargetEntityGetter()->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
             if (transformTest != nullptr)
             {
                 auto moveBehaviour = std::make_shared<Game::MoveBehaviour>(transformTest, 5.0f);
             systemsManager->GetSystem<LogicSystem>().AddBehaviour(static_cast<Engine::BehaviourFCT*>(moveBehaviour.get()));
             }

         }
         */

        while (m_Running)
        {
            auto loopStartTime = std::chrono::high_resolution_clock::now();
            glfwPollEvents();
            auto currentTime = std::chrono::high_resolution_clock::now();
            double deltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - previousTime).count();
            previousTime = currentTime;
            UpdateDeltaTime();
            Application::UpdateWindowTitle();

            UpdateWindowFocus();

            // Main menu test
            if (InputHandler.IsKeyTriggered(KEY_M)) {
                mainMenu->TransitionToGame();  // Transition to the next scene (you can bind this to any key you like)
            }

            if (!isPaused || stepOneFrame) {
                accumulatedTime += (stepOneFrame ? fixedDeltaTime : deltaTime);
                if (stepOneFrame) {
                    isPaused = true; // Automatically pause after stepping one frame
                    stepOneFrame = false;

                }                 
            }

            if (InputHandler.IsKeyTriggered(KEY_F7)) {
                isPaused = !isPaused;
            }

            // Step one frame forward
            if (isPaused && InputHandler.IsKeyTriggered(KEY_F8)) {
                stepOneFrame = true;
            }
            //std::cout << InputHandler.GetMousePosition().x << " x "<< InputHandler.GetMousePosition().y << std::endl;  
            currentNumberOfSteps = 0;
            while (accumulatedTime >= fixedDeltaTime) {
                accumulatedTime -= fixedDeltaTime;
                currentNumberOfSteps++;
                InputHandler.Update();
                m_Window->OnUpdate();

                // Audio handling based on key input
                if (InputHandler.IsKeyTriggered(KEY_3)) {
                    audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_Win"))));
                    //currentlyPlayingSound = false;
                }

                if (InputHandler.IsKeyTriggered(KEY_5)) {
                    audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_Arrow)"))));
                    //currentlyPlayingSound = false;
                }

                if (InputHandler.IsKeyTriggered(KEY_7)) {
                    audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_Slash"))));
                    //currentlyPlayingSound = false;
                }

                if (InputHandler.IsKeyTriggered(KEY_4) && audioEngine.soundIsPlaying(*(assetManager->getAudio(AudioKey("sound_Win"))))) {
                    audioEngine.stopSound(*(assetManager->getAudio(AudioKey("sound_Win"))));
                    currentlyPlayingSound = false;
                }

                if (InputHandler.IsKeyTriggered(KEY_6) && audioEngine.soundIsPlaying(*(assetManager->getAudio(AudioKey("sound_Arrow"))))) {
                    audioEngine.stopSound(*(assetManager->getAudio(AudioKey("sound_Arrow"))));
                    currentlyPlayingSound = false;
                }

                if (InputHandler.IsKeyTriggered(KEY_8) && audioEngine.soundIsPlaying(*(assetManager->getAudio(AudioKey("sound_Slash"))))) {
                    audioEngine.stopSound(*(assetManager->getAudio(AudioKey("sound_Slash"))));
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

                //// Getting collision component data to m_inGameGUI
                //if (m_inGameGUI->TargetEntityGetter()->HasComponent(ComponentType::Collision)) {
                //    collisionTest = dynamic_cast<CollisionComponent*>(m_inGameGUI->TargetEntityGetter()->GetComponent(ComponentType::Collision));
                //}

                // Define a threshold for the minimum and maximum scales
                const float minScale = 0.5f; // Adjust this value as needed
                const float maxScale = 2.0f; // Adjust this value as needed

                // Add a flag to keep track of scaling direction
                bool scalingUp = false;
                bool scalingDown = false;

                float lastPositionX = 0.0f, lastPositionY = 0.0f, nextPositionX = 0.0f, nextPositionY = 0.0f;
                // Variables for last position
                if (transformTest != nullptr) {
                    lastPositionX = transformTest->position.x;
                    lastPositionY = transformTest->position.y;
                    nextPositionX = lastPositionX + 1;
                    nextPositionY = lastPositionY + 1;
                }

                //if (collisionTest->mColliding) {
                //    std::cout << "Hello" << std::endl;
                //}

                if (collisionTest && transformTest) //INPUT TESTING FOR UNIT ENTITIES
                {

                    if (collisionTest->isColliding && towerCollision == false) {
                        //audioEngine.playSound(sound_Slash);
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
                        collisionTest->collisionVel.y += transformation;
                        transformTest->position.y = lastPositionY;
                        //if (physicsTest->velocity.y <= 0.0f) {
                        //    physicsTest->velocity.y = 1.0f - friction;
                        //}
                        lastKeyPressed = 1;
                    }

                    else if (InputHandler.IsKeyPressed(KEY_DOWN) && !(collisionTest->isColliding))
                    {
                        lastPositionY -= transformation;
                        collisionTest->collisionVel.y -= transformation;
                        transformTest->position.y = lastPositionY;
                        //if (physicsTest->velocity.y >= -0.0f) {
                        //    physicsTest->velocity.y = -1.0f + friction;
                        //}
                        lastKeyPressed = 2;
                    }

                    else if (InputHandler.IsKeyPressed(KEY_LEFT) && !(collisionTest->isColliding))
                    {
                        lastPositionX -= transformation;
                        collisionTest->collisionVel.x -= transformation;
                        transformTest->position.x = lastPositionX;
                        //if (physicsTest->velocity.x >= -0.0f) {
                        //    physicsTest->velocity.x = -1.0f + friction;
                        //}
                        lastKeyPressed = 3;
                    }

                    else if (InputHandler.IsKeyPressed(KEY_RIGHT) && !(collisionTest->isColliding))
                    {
                        lastPositionX += transformation;
                        collisionTest->collisionVel.x += transformation;
                        transformTest->position.x = lastPositionX;
                        //if (physicsTest->velocity.x <= 0.0f) {
                        //    physicsTest->velocity.x = 1.0f - friction;
                        //}
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
                    //else
                    //{
                    //    physicsTest->velocity.x = 0.0f;
                    //    physicsTest->velocity.y = 0.0f;
                    //}
                }

            }         
            
            audioEngine.update();
            //System Updating
            systemsManager->UpdateSystems(EM->GetEntities());
            auto loopEndTime = std::chrono::high_resolution_clock::now();
            loopTime = std::chrono::duration_cast<std::chrono::microseconds>(loopEndTime - loopStartTime).count() / 1000.0; // Convert to milliseconds
            m_ImGuiWrapper->Begin();
            m_ImGuiWrapper->OnUpdate();
            m_ImGuiWrapper->End();
            m_inGameGUI->Update(buttonCollision);
            systemsManager->ResetSystemTimers();
            if (InputHandler.IsKeyTriggered(KEY_ESCAPE))
                m_Running = false;

            // Reset system timers for the next loop iteration
            /*
            if (InputHandler.IsKeyTriggered(KEY_F12)) // Use any key you like, for this example I'm using 'C'
            {
                int* crashPointer = nullptr;
                *crashPointer = 42; // This will cause a read access violation, simulating a crash
            }
            */
        }           
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        UNREFERENCED_PARAMETER(e);
        // Handle window close event
        loader->SavePrefabs("Resource/Prefabs.txt");
        glfwTerminate();
        m_Running = false;
        return true;
    }

    bool Application::OnWindowResize(WindowResizeEvent& e)
    {
        // Update the viewport and projection matrix
        //float previousWidth = e_Width;
        //float previousHeight = e_Height;
        int newWidth = e.GetWidth();
        int newHeight = e.GetHeight();
        //float scaleWidth = (newWidth / previousWidth);
        //float scaleHeight = (newHeight / previousHeight);
        //VECTORMATH::Vector2D scale = {  scaleWidth, scaleHeight };

        graphicsSystem->UpdateViewport(newWidth, newHeight);  

        //std::cout << scaleWidth << ", " << scaleHeight << std::endl;
        //std::cout << newWidth << ", " << newHeight << std::endl;

        return true;
    }

    void Application::UpdateDeltaTime()
    {
        static int frameCount = 0;
        // Calculate delta time (time between frames)
        double currentTime = glfwGetTime();
        
        dt = currentTime - prevTime;
        frameCount++;
        if (dt >= 1.0)
        {
            // Calculate frames per second (FPS)
            fps = double(frameCount) / dt;
            frameCount = 0;
            prevTime = currentTime;
        }
    }

    bool Application::TimePassed(double seconds)
    {
        // Use static to make sure the startTime is persistent across function calls
        static std::chrono::high_resolution_clock::time_point startTime = std::chrono::high_resolution_clock::now();

        // Calculate elapsed time since the start
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime).count();

        // Check if the elapsed time is greater than or equal to the specified seconds
        bool result = elapsedTime >= seconds;

        std::cout << "My boolean value is: " << std::boolalpha << result << std::endl;
        std::cout << "Elapsed time is: " << elapsedTime << " seconds" << std::endl;

        // If the specified time has passed, reset the startTime to the current time
        if (result)
        {
            startTime = currentTime;
        }

        return result;
    }


    void Application::UpdateWindowFocus() {
        if (m_Window) {
            // Use get() to obtain a raw pointer to the managed object
            Engine::WindowsWindow* windowsWindow = dynamic_cast<Engine::WindowsWindow*>(m_Window.get());

            if (windowsWindow) {
                // Check if the window is currently focused
                bool isFocused = glfwGetWindowAttrib(windowsWindow->GetNativeWindow(), GLFW_FOCUSED) != 0;

                // If the window is not focused or is iconified (minimized)
                if (!isFocused || glfwGetWindowAttrib(windowsWindow->GetNativeWindow(), GLFW_ICONIFIED)) {
                    // Minimize the window, pause the game, and pause all audio playback
                    //windowsWindow->MinimizeWindow();
                    isPaused = true;
                    audioEngine.pauseAllAudio();
                    Logger::GetInstance().Log(LogLevel::Debug, "Window lost focus. Pausing game and audio.");
                }
                // If the window is focused
                else {
                    // If the window was maximized, restore it
                    if (windowsWindow->IsWindowMaximized()) {
                        windowsWindow->RestoreWindow();
                    }
                    // Unpause the game, resume audio playback, and log the event
                    isPaused = false;
                    audioEngine.resumeAllAudio();
                    Logger::GetInstance().Log(LogLevel::Debug, "Window regained focus. Resuming game and audio.");
                }
            }
        }
    }

    void Application::UpdateWindowTitle() 
    {
        std::string title_str = windowProps.Title;

        // Append FPS information in debug mode only
#ifdef DEBUG
        std::stringstream ss;
        ss << std::fixed << std::setprecision(2) << fps;
        std::string fps_str = ss.str();
        title_str += " | FPS: " + fps_str;
#endif

        glfwSetWindowTitle(glfwGetCurrentContext(), title_str.c_str());
    }
}