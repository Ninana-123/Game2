/******************************************************************************/
/*!
\file		Application.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\co         Wayne Kwok Jun Lin (10%)
\par        email: k.junlinwayne@digipen.edu
\date   	29/09/2923
\brief		This file contains the declaration of the main application class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_APPLICATION_H
#define ENGINE_APPLICATION_H

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
extern int e_Width;
extern int e_Height;
extern bool mainMenuCheck;
extern double fps;

namespace Engine
{
    // Application class definition
    class GAME2_API Application
    {
    public:

        /*!**********************************************************************
        \brief
        Constructor for the Application class
        *************************************************************************/
        Application();

        /*!**********************************************************************
        \brief
        Destructor for the Application class
        *************************************************************************/
        virtual ~Application();

        /*!**********************************************************************
        \brief
        Initialize the application
        This function initializes various components and systems needed
        for the application to run.
        *************************************************************************/
        void Initialize();

        /*!**********************************************************************
        \brief
        Run the application
        This function runs the main loop of the application, handling input,
        updating systems, and rendering.
        *************************************************************************/
        void Run();

        /*!**********************************************************************
        \brief
        Event handler for processing events
        This function handles incoming events and dispatches them accordingly.
        *************************************************************************/
        void OnEvent(Event& e);

        // Window instance
        WindowsWindow window;

        // Get a reference to the application instance (Singleton pattern)
        static Application& Get()
        {
            static Application instance; // Create a single instance on first access
            return instance;
        }

        /*!**********************************************************************
        \brief
        Updates the delta time and calculates frames per second (FPS).
        *************************************************************************/
        void UpdateDeltaTime();

        static bool TimePassed(double seconds);

        /*!**********************************************************************
        \brief
        Updates the window title to display FPS.
        *************************************************************************/
        void UpdateWindowTitle();

        /*!**********************************************************************
         * \brief Updates the focus state of the application window.
         *
         * This function is responsible for handling changes in window focus and taking
         * appropriate actions, such as minimizing or restoring the window, pausing or
         * resuming the game, and controlling audio playback.
         *************************************************************************/
        void UpdateWindowFocus();

        // Asset manager instance
        std::shared_ptr<Engine::AssetManager> assetManager;

        // Entity manager instance
        std::shared_ptr<Engine::EntityManager> EM;      

        void ToggleFullscreen();

    private:

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
        bool OnWindowClose(WindowCloseEvent& e);

        /*!**********************************************************************
        \brief
        Handles the window resize event.
        This function handles the event triggered when the application's
        window is resized.
        \param[in] e
        WindowResizeEvent object containing event information.
        *************************************************************************/
        bool OnWindowResize(WindowResizeEvent& e);

       //void TransitionToNextScene();

        // Window instance 
        std::unique_ptr<Window> m_Window;

        // Flag indicating if the application is running
        bool m_Running = true;
        bool gamePlaying = true;
        bool isMainMenuLoaded = false;
        //// Assuming width_texture and height_texture are known
        //float width_texture ;
        //float height_texture;
        //float scaleX = 2.7f;  // Scale factor in the X direction
        //float scaleY = 2.4f;  // Scale factor in the Y direction

        //float estimated_width = width_texture * scaleX;
        //float estimated_height = height_texture * scaleY;

        //// Position of the play button entity
        //float playButtonX = 335.0f;  // X position of the play button
        //float playButtonY = -50.0f;   // Y position of the play button

        //// Calculate boundaries of the play button
        //float playButtonLeft = playButtonX - estimated_width / 2.0f;
        //float playButtonRight = playButtonX + estimated_width / 2.0f;
        //float playButtonTop = playButtonY + estimated_height / 2.0f;
        //float playButtonBottom = playButtonY - estimated_height / 2.0f;

    };

    /*!
    ***********************************************************************
    \brief
    Function to create an application instance.
    \return
    A pointer to the created Application instance.
    ***********************************************************************/
    Application* CreateApplication();

} // End of namespace Engine
#endif ENGINE_APPLICATION_H