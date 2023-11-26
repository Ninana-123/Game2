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
#include "AudioEngine.h"
#include <GLFW/glfw3.h>

//extern bool isWindowmin;

namespace Engine {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowConfig& props);
		virtual ~WindowsWindow();
		WindowsWindow() = default; // Default constructor
		void OnUpdate();

		inline  unsigned int GetWidth()  const { return m_Data.Width; }
		inline  unsigned int GetHeight() const { return m_Data.Height; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		inline virtual void* GetNativeWindow() const { return m_Window; }
		void MinimizeWindow();
		void RestoreWindow();

	private:
		virtual void Init(const WindowConfig& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;
		struct WindowData {
			std::string Title;
			unsigned int Width = 0;  // Initialize to a default value
			unsigned int Height = 0; // Initialize to a default value

        /**
         * @brief Restores the window.
         */
        void RestoreWindow();

		AudioEngine audio;
		WindowData m_Data;
		bool m_IsMaximized = false;
		bool m_IsFocused = true;
    	};
    }
}