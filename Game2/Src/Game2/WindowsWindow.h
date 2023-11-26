/******************************************************************************/
/*!
\file		WindowsWindow.h
\author 	Liu Xujie
\co         Wayne Kwok Jun Lin (20%)
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Declaration of the WindowsWindow class, derived from the
			Window class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
    class WindowsWindow : public Window {
    public:
        /**
         * @brief Constructor for the WindowsWindow class.
         * @param props The WindowConfig containing the window properties.
         */
        WindowsWindow(const WindowConfig& props);

        /**
         * @brief Destructor for the WindowsWindow class.
         */
        virtual ~WindowsWindow();

        /**
         * @brief Updates the WindowsWindow by processing events and swapping buffers.
         */
        void OnUpdate();

        /**
         * @brief Minimizes the window.
         */
        void MinimizeWindow();

        /**
         * @brief Restores the window.
         */
        void RestoreWindow();

        /**
         * @brief Default constructor.
         */
        WindowsWindow() = default;

        /**
         * @brief Gets the width of the window.
         * @return The width of the window.
         */
        inline unsigned int GetWidth() const { return m_Data.Width; }

        /**
         * @brief Gets the height of the window.
         * @return The height of the window.
         */
        inline unsigned int GetHeight() const { return m_Data.Height; }

        /**
         * @brief Sets the event callback function for the window.
         * @param callback The callback function to set.
         */
        inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

        /**
         * @brief Gets the native window handle.
         * @return A pointer to the native window handle.
         */
        inline virtual void* GetNativeWindow() const { return m_Window; }

    private:
        /**
         * @brief Initializes the WindowsWindow using the provided WindowConfig properties.
         *        It sets up the GLFW window and sets appropriate GLFW hints for window creation.
         * @param props The WindowConfig containing the window properties.
         */
        virtual void Init(const WindowConfig& props);

        /**
         * @brief Shuts down the WindowsWindow, destroying the GLFW window.
         */
        virtual void Shutdown();

    private:
        GLFWwindow* m_Window;

        struct WindowData {
            std::string Title;
            unsigned int Width = 0;  // Initialize to a default value
            unsigned int Height = 0; // Initialize to a default value

            EventCallbackFn EventCallback;
        };

        WindowData m_Data;
        bool m_IsMaximized = false;
        bool m_IsFocused = true;
    };
}