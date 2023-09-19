#pragma once

#include "Core.h"
#include "Window.h"
#include "Logger.h"
#include "Event.h"
#include "AppEvent.h"


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

        // Run the application
        void Run();

        // Event handler
        void OnEvent(Event& e);

        // Get the application window
        inline Window& GetWindow() { return *m_Window; }

        // Get a reference to the application instance (Singleton pattern)
        static Application& Get()
        {
            static Application instance; // Create a single instance on first access
            return instance;
        }

        void UpdateDeltaTime();
        void UpdateWindowTitle();


    private:
        // Handle the window close event
        bool OnWindowClose(WindowCloseEvent& e);

        // Window instance (ownership managed by a smart pointer)
        std::unique_ptr<Window> m_Window;

        // Flag indicating if the application is running
        bool m_Running = true;
    };

    // Function to create an application instance
    Application* CreateApplication();

} // End of namespace Engine
