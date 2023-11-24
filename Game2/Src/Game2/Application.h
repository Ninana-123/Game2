/******************************************************************************/
/*!
\file		Application.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		This file contains the declaration of the main application class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "Core.h"
#include "Window.h"
#include "AppEvent.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "WindowsWindow.h"

extern double loopTime;
extern const double fixedDeltaTime;
extern int currentNumberOfSteps;
extern bool isPaused;
extern bool stepOneFrame;
extern double dt;
extern std::string initScene;


namespace Engine
{
    // Application class definition
    class GAME2_API Application
    {
    public:
        // Constructor
        Application();

        // Destructor
        virtual ~Application();

        void Initialize();

        // Run the application
        void Run();

        // Event handler
        void OnEvent(Event& e);

       
        WindowsWindow window;

        // Get a reference to the application instance (Singleton pattern)
        static Application& Get()
        {
            static Application instance; // Create a single instance on first access
            return instance;
        }

        void UpdateDeltaTime();
        void UpdateWindowTitle();

        std::shared_ptr<Engine::AssetManager> assetManager;
        std::shared_ptr<Engine::EntityManager> EM;        

    private:
        // Handle the window close event
        bool OnWindowClose(WindowCloseEvent& e);

        void OnWindowResize(WindowResizeEvent& e);

        // Window instance (ownership managed by a smart pointer)
        std::unique_ptr<Window> m_Window;

        // Flag indicating if the application is running
        bool m_Running = true;

        
    };

    // Function to create an application instance
    Application* CreateApplication();

} // End of namespace Engine
