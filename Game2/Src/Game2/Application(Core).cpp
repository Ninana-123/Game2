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
#include "ShootingSystem.h"
#include "WindowsWindow.h"
#include "Input.h"
#include "SceneManager.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "CutScene.h"
#include "TempStateMachine.h"
#include "Vector2d.h"
#include "ScriptFactory.h"

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
bool mainMenuCheck = true;
std::string fp;
std::shared_ptr<Engine::ImGuiWrapper> m_ImGuiWrapper = nullptr;

//std::string initScene = "Resource/Scenes/MainMenu.txt";
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
    std::shared_ptr<SystemsManager> systemsManager = nullptr;
    std::shared_ptr<inGameGUI> m_inGameGUI = nullptr;
    std::shared_ptr<ShootingSystem> m_shootingSystem = nullptr;

    // Entity-related instances and properties
    GraphicsSystem* graphicsSystem;
    CollisionSystem* collisionSystem;
    std::shared_ptr<EntityManager> EM;   
    PrefabManager PM;
    EntityID cloneEntity;
    Entity* targetEntity;
    TransformComponent* transformTest;
    CollisionComponent* collisionTest;
    PhysicsComponent* physicsTest;
    TextureComponent* textureTest;
    ComponentFactory CF;
    ScriptSystem scriptSystem(EM);
    ScriptFactory g_ScriptFactory(scriptSystem);
    StateMachine SM;
    //TextureClass textureClass;
    //FileBrowser fileBrowser;

    SceneManager sceneManager;
    //MainMenuScene mainMenuScene;
    //GameScene gameScene;

    float scalar = 0.1f;
    float rotation = 0.125f;
    int transformation = 5;

    bool tower1DownSoundPlayed = false;
    bool tower2DownSoundPlayed = false;
 

    // Flag to track if a sound is currently playing
    bool currentlyPlayingSound = 0;
#ifdef DEBUG
    bool isFullScreen = false;
#else
    bool isFullScreen = true;
#endif

    Application::Application()
    {

    }

    Application::~Application()
    {

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
            for (int subIndex = 0; subIndex <= 5; ++subIndex) {
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
        //loader = std::make_unique<Engine::Loader>(EM, &PM, assetManager);
        loader = std::make_shared<Engine::Loader>(EM, &PM, assetManager);

        Logger::GetInstance().Log(LogLevel::Debug, "Loading Scene");
        //loader->LoadScene(initScene);
        Logger::GetInstance().Log(LogLevel::Debug, "Scene Loaded");
        Logger::GetInstance().Log(LogLevel::Debug, "Loading Prefabs");
        loader->LoadPrefabs("Resource/Prefabs/Prefabs.txt");
        Logger::GetInstance().Log(LogLevel::Debug, "Prefabs Loaded");

        sceneManager.TransitionToScene(std::make_shared<MainMenuScene>(EM, &PM, assetManager));
        isMainMenuLoaded = true;

        if (EM->GetEntity(1) != nullptr) {
            targetEntity = EM->GetEntity(1);
            transformTest = dynamic_cast<TransformComponent*>(targetEntity->GetComponent(ComponentType::Transform)); //reference to Entity Transform data
            collisionTest = dynamic_cast<CollisionComponent*>(targetEntity->GetComponent(ComponentType::Collision));
            physicsTest = dynamic_cast<PhysicsComponent*>(targetEntity->GetComponent(ComponentType::Physics));
            textureTest = dynamic_cast<TextureComponent*>(targetEntity->GetComponent(ComponentType::Texture));
        }
        else
            targetEntity = EM->GetEntity(0);

        // Initialize audio files and load sounds
        audioEngine.init();
        assetManager->AddAudioPath(AudioKey("sound_BGM"), "Resource/Audio/level_bgm.wav");
        assetManager->loadAudio(AudioKey("sound_BGM"), true);
        
        assetManager->AddAudioPath(AudioKey("mainmenu_BGM"), "Resource/Audio/mainmenu_bgm.wav");
        assetManager->loadAudio(AudioKey("mainmenu_BGM"), true);
        
        assetManager->AddAudioPath(AudioKey("sound_Win"), "Resource/Audio/levelwin.wav");
        assetManager->loadAudio(AudioKey("sound_Win"), false);
        assetManager->getAudio(AudioKey("sound_Win"))->setVolume(0.5f);

        assetManager->AddAudioPath(AudioKey("sound_Arrow"), "Resource/Audio/archer_shoot.wav");
        assetManager->loadAudio(AudioKey("sound_Arrow"), false);
        assetManager->getAudio(AudioKey("sound_Arrow"))->setVolume(0.5f);

        assetManager->AddAudioPath(AudioKey("sound_Slash"), "Resource/Audio/samurai_slash.wav");
        assetManager->loadAudio(AudioKey("sound_Slash"), false);
        assetManager->getAudio(AudioKey("sound_Slash"))->setVolume(0.3f);

        assetManager->AddAudioPath(AudioKey("sound_Ambience"), "Resource/Audio/forest_ambience.wav");
        assetManager->loadAudio(AudioKey("sound_Ambience"), true);
        assetManager->getAudio(AudioKey("sound_Ambience"))->setVolume(0.5f);

        assetManager->AddAudioPath(AudioKey("sound_Foot1"), "Resource/Audio/Footsteps/Footsteps1.wav");
        assetManager->loadAudio(AudioKey("sound_Foot1"), false);
        assetManager->getAudio(AudioKey("sound_Foot1"))->setVolume(0.3f);

        assetManager->AddAudioPath(AudioKey("sound_Foot2"), "Resource/Audio/Footsteps/Footsteps2.wav");
        assetManager->loadAudio(AudioKey("sound_Foot2"), false);
        assetManager->getAudio(AudioKey("sound_Foot2"))->setVolume(0.3f);

        assetManager->AddAudioPath(AudioKey("sound_Swipe"), "Resource/Audio/tank_attack.wav");
        assetManager->loadAudio(AudioKey("sound_Swipe"), true);
        assetManager->getAudio(AudioKey("sound_Swipe"))->setVolume(0.3f);

        assetManager->AddAudioPath(AudioKey("tower_Down"), "Resource/Audio/tower_fall.wav");
        assetManager->loadAudio(AudioKey("tower_Down"), false);
        assetManager->getAudio(AudioKey("tower_Down"))->setVolume(1.0f);

        assetManager->AddAudioPath(AudioKey("button_Click"), "Resource/Audio/button_click.wav");
        assetManager->loadAudio(AudioKey("button_Click"), false);
        assetManager->getAudio(AudioKey("button_Click"))->setVolume(1.0f);

        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_BGM"), true)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("mainmenu_BGM"), true)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Win"), false)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Arrow"), false)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Slash"), false)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Ambience"), true)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Foot1"), true)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Foot2"), true)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("sound_Swipe"), true)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("tower_Down"), false)));
        audioEngine.loadSound(*(assetManager->loadAudio(AudioKey("button_Click"), false)));

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

        // Initialize inGameGUI
        m_shootingSystem = std::make_unique<Engine::ShootingSystem>(EM, &PM, collisionSystem);

        //Attaching Input Handler to EM
        InputHandler.SetEntityManager(EM);
        InputHandler.SetImGuiWrapper(m_ImGuiWrapper);

        //fileBrowser.setSelectedEntityIndexReference(selectedEntityIndex);
        //fileBrowser.setLoader(deserializer);
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
        if (isMainMenuLoaded) {
            if (e.GetEventType() == EventType::MouseButtonPressed)
            {   
               

                MouseButtonPressedEvent& mousePressedEvent = dynamic_cast<MouseButtonPressedEvent&>(e);
                if (mousePressedEvent.GetMouseButton() == LEFT_MOUSE_BUTTON)
                {
                    // Check if the mouse click is within the quadrilateral
                    mousePressedEvent.SetX(InputHandler.GetMouseX());
                    mousePressedEvent.SetY(InputHandler.GetMouseY());
                    float mouseX = mousePressedEvent.GetX();
                    float mouseY = mousePressedEvent.GetY();

                    if (IsPointInQuadrilateral(mouseX, mouseY, 603, 305, 719, 308, 725, 367, 597, 353))
                    {
              
                        fp = GameSceneFilePath;
                        int entityCount = static_cast<int>(EM->GetEntities()->size());

                        for (int i = entityCount - 1; i >= 0; --i) {
                            EM->DestroyEntity(i); 
                        }

                        m_ImGuiWrapper->selectedEntityIndex = -1;

                        // Set targetEntity to nullptr as there are no entities left
                        m_ImGuiWrapper->SetTargetEntity(nullptr);

                        // Reset any other relevant data structures or counters if needed
                        EM->nextEntityID = 0; // Assuming this is how you reset your IDs
                        PM.nextPrefabID = 0; // Reset prefab ID counter if needed

                        // Now load the scene
                        loader->LoadScene(fp);
                        if (EM->GetEntities()->size() >= 2) {
                            m_ImGuiWrapper->selectedEntityIndex = 1;
                        }
                        else if (EM->GetEntities()->size() == 1) {
                            m_ImGuiWrapper->selectedEntityIndex = 0;
                        }
                        else
                            m_ImGuiWrapper->selectedEntityIndex = -1;
                        if (EM->GetEntity(m_ImGuiWrapper->selectedEntityIndex) != nullptr) {
                            m_ImGuiWrapper->SetTargetEntity(EM->GetEntity(m_ImGuiWrapper->selectedEntityIndex));
                        }
                        mainMenuCheck = false;
                        isMainMenuLoaded = false;
                        audioEngine.stopSound(*(assetManager->getAudio(AudioKey("mainmenu_BGM"))));
                        audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_BGM"))));
                        audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_Ambience"))));
                    }
                }
            
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

        audioEngine.playSound(*(assetManager->getAudio(AudioKey("mainmenu_BGM"))));

    /*    if (isMainMenuLoaded) {
            audioEngine.playSound(*(assetManager->getAudio(AudioKey("mainmenu_BGM"))));
        }

        else if (!isMainMenuLoaded) {
            audioEngine.stopSound(*(assetManager->getAudio(AudioKey("mainmenu_BGM"))));
            audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_BGM"))));
            audioEngine.playSound(*(assetManager->getAudio(AudioKey("sound_Ambience"))));
        }*/

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

                if (InputHandler.IsKeyTriggered(KEY_F5))
                    fpsTimer = !fpsTimer;
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

                if (InputHandler.IsKeyTriggered(KEY_DOWN)) {
                    audioEngine.decreaseVolume();
                }

                if (InputHandler.IsKeyTriggered(KEY_UP)) {
                    audioEngine.increaseVolume();
                }
               
                if (InputHandler.IsMouseClicked(0)) {
                    audioEngine.playSound(*(assetManager->getAudio(AudioKey("button_Click"))));
                    //currentlyPlayingSound = false;
                }


                 //Check if tower1 is destroyed and if the sound hasn't been played yet
                if (tower1Destroyed && !tower1DownSoundPlayed) {
                    audioEngine.playSound(*(assetManager->getAudio(AudioKey("tower_Down"))));

                    // Set towerDownSoundPlayed to true to indicate that the sound has been played
                    tower1DownSoundPlayed = true;
                }

                // Check if tower1 is not destroyed and if the sound has been played
                else if (!tower1Destroyed && tower1DownSoundPlayed) {
                   // Stop the sound
                    audioEngine.stopSound(*(assetManager->getAudio(AudioKey("tower_Down"))));

                    // Reset towerDownSoundPlayed to false to indicate that the sound has stopped
                    tower1DownSoundPlayed = false;
                }

                //Check if tower1 is destroyed and if the sound hasn't been played yet
                if (tower2Destroyed && !tower2DownSoundPlayed) {
                    audioEngine.playSound(*(assetManager->getAudio(AudioKey("tower_Down"))));

                    // Set towerDownSoundPlayed to true to indicate that the sound has been played
                    tower2DownSoundPlayed = true;
                }

                // Check if tower1 is not destroyed and if the sound has been played
                else if (!tower2Destroyed && tower2DownSoundPlayed) {
                    // Stop the sound
                    audioEngine.stopSound(*(assetManager->getAudio(AudioKey("tower_Down"))));

                    // Reset towerDownSoundPlayed to false to indicate that the sound has stopped
                    tower2DownSoundPlayed = false;
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

                if (collisionTest && transformTest && textureTest) //INPUT TESTING FOR UNIT ENTITIES
                {

                    if (collisionTest->isColliding) {
                        if (textureTest->textureKey.mainIndex == 1 || textureTest->textureKey.mainIndex == 2 ||
                            textureTest->textureKey.mainIndex == 3) {
                            //audioEngine.playSound(sound_Slash);
                            if ((lastPositionY < nextPositionY)) {
                                transformTest->position.y = lastPositionY - 10.f;
                            }
                            if ((lastPositionY > nextPositionY)) {
                                transformTest->position.y = lastPositionY + 10.f;
                            }
                            if ((lastPositionX < nextPositionX)) {
                                transformTest->position.x = lastPositionX + 10.f;
                            }
                            if ((lastPositionX > nextPositionX)) {
                                transformTest->position.x = lastPositionX - 10.f;
                            }
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
            (void)systemsManager->UpdateSystems(EM->GetEntities());
            SM.UpdateEntities(EM->GetEntities(), audioEngine, *assetManager);
            auto loopEndTime = std::chrono::high_resolution_clock::now();
            loopTime = std::chrono::duration_cast<std::chrono::microseconds>(loopEndTime - loopStartTime).count() / 1000.0; // Convert to milliseconds
            m_ImGuiWrapper->Begin();
            m_ImGuiWrapper->OnUpdate();
            m_ImGuiWrapper->End();
            m_inGameGUI->Update(buttonCollision, audioEngine, *assetManager);
            m_shootingSystem->Update(static_cast<float>(deltaTime), isShooting, EM->GetEntities(), *assetManager, audioEngine);
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

        //std::cout << "My boolean value is: " << std::boolalpha << result << std::endl;
        //std::cout << "Elapsed time is: " << elapsedTime << " seconds" << std::endl;

        // If the specified time has passed, reset the startTime to the current time
        if (result)
        {
            startTime = currentTime;
        }

        return result;
    }

    float Application::ElapsedTime(PathfindingComponent* pathfindingComponent, double seconds)
    {
        // Check if the entity has a valid pathfinding component
        if (pathfindingComponent == nullptr)
            return 0.0f; // Return 0 if the component is invalid

        // Use the stored startTime within the pathfinding component
        auto& startTime = pathfindingComponent->startTime;

        // Calculate elapsed time since the start
        auto currentTime = std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(currentTime - startTime).count();

        bool result = elapsedTime >= seconds;

        // If the specified time has passed, reset the startTime to the current time
        if (result)
        {
            startTime = currentTime;
        }

        return static_cast<float>(elapsedTime);
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
                    // Logger::GetInstance().Log(LogLevel::Debug, "Window lost focus. Pausing game and audio.");
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
                    // Logger::GetInstance().Log(LogLevel::Debug, "Window regained focus. Resuming game and audio.");
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

    //void Application::LoadScene()
    //{
    //    if (deleteAllEntity == true)
    //    {
    //        // Retrieve the size of entities list
    //        int entityCount = static_cast<int>(entityManager->GetEntities()->size());

    //        // Loop backwards through the entities and delete each one
    //        for (int i = entityCount - 1; i >= 0; --i)
    //        {
    //            entityManager->DestroyEntity(i); // Assumes DestroyEntity accepts an index
    //        }

    //        // Reset the selected entity index as there are no entities to select
    //        selectedEntityIndex = -1;

    //        // Set targetEntity to nullptr as there are no entities left
    //        targetEntity = nullptr;

    //        // Reset any other relevant data structures or counters if needed
    //        entityManager->nextEntityID = 0; // Assuming this is how you reset your IDs
    //        prefabManager->nextPrefabID = 0; // Reset prefab ID counter if needed

    //        std::cout << "Deleted All Entities" << std::endl;
    //        deleteAllEntity = false;
    //    }

    //    // Now load the scene
    //    deserializer->LoadScene(sceneToLoad);
    //    if (entityManager->GetEntities()->size() >= 2) {
    //        selectedEntityIndex = 1;
    //    }
    //    else if (entityManager->GetEntities()->size() == 1) {
    //        selectedEntityIndex = 0;
    //    }
    //    else
    //        selectedEntityIndex = -1;
    //    if (entityManager->GetEntity(selectedEntityIndex) != nullptr) {
    //        targetEntity = entityManager->GetEntity(selectedEntityIndex);
    //    }
    //    shouldLoadScene = false; // Reset flag
    //}
    bool Application::IsPointInQuadrilateral(float x, float y, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
    {
        // Use ray casting algorithm to determine if the point is inside the quadrilateral
        int intersectCount = 0;

        // Check for intersections with each edge of the quadrilateral
        if (DoIntersect(x, y, x1, y1, x2, y2)) intersectCount++;
        if (DoIntersect(x, y, x2, y2, x3, y3)) intersectCount++;
        if (DoIntersect(x, y, x3, y3, x4, y4)) intersectCount++;
        if (DoIntersect(x, y, x4, y4, x1, y1)) intersectCount++;

        // If the number of intersections is odd, the point is inside the quadrilateral
        return intersectCount % 2 == 1;
    }

    // Function to check if a point intersects with a line segment
    bool Application::DoIntersect(float pX, float pY, float qX, float qY, float rX, float rY)
    {
        return (qY > pY) != (rY > pY) && pX < (rX - qX) * (pY - qY) / (rY - qY) + qX;
    }


}