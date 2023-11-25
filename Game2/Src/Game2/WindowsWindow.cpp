/******************************************************************************/
/*!
\file		WindowsWindow.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Implementation of the WindowsWindow class, derived from the 
			Window class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "WindowsWindow.h"
#include "AppEvent.h"
#include "InputEvent.h"
#include "AudioEngine.h"

namespace Engine {
	// Static flag to check if GLFW is initialized
	static bool s_GLFWInitialized = false;

	/*!**********************************************************************
	\brief
	Error callback function for GLFW
	\param[in] error
	The error code
	\param[in] description 
	Description of the error
	*************************************************************************/
	static void GLFWErrorCallback(int error, const char* description) {
		UNREFERENCED_PARAMETER(error);
		Logger::GetInstance().Log(Engine::LogLevel::Error, description);
	}

	/*!**********************************************************************
	\brief
	Factory method to create a Window object based on the 
	provided WindowConfig properties.
	\param[in] props 
	The WindowConfig containing the window properties.
	\return
	A pointer to the created Window object.
	*************************************************************************/
	Window* Window::Create(const WindowConfig& props) {
		return new WindowsWindow(props);
	}

	/*!**********************************************************************
	\brief
	Constructor for the WindowsWindow class.
	\param[in] props
	The WindowConfig containing the window properties.
	*************************************************************************/
	WindowsWindow::WindowsWindow(const WindowConfig& props) {
		Init(props);
	}


	/*!**********************************************************************
	\brief
	Destructor for the WindowsWindow class.
	*************************************************************************/	
	WindowsWindow::~WindowsWindow() {
	}

	/*!**********************************************************************
	\brief
	Initializes the WindowsWindow using the provided WindowConfig properties.
	It sets up the GLFW window and sets appropriate GLFW hints
	for window creation.
	\param[in] props
	The WindowConfig containing the window properties.
	*************************************************************************/

	void WindowsWindow::Init(const WindowConfig& props) {
		// Initialize window properties
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;



		// Log window creation information
		Logger::GetInstance().Log(Engine::LogLevel::Info, "Creating Window " + props.Title + " (" + std::to_string(props.Width) + ", " + std::to_string(props.Height) + ")");

		// Initialize GLFW if not already initialized
		if (!s_GLFWInitialized) {
			int success = glfwInit();
			glfwSetErrorCallback(GLFWErrorCallback);
			if (!success) {
				Logger::GetInstance().Log(LogLevel::Error, "Failed to initialize GLFW.");
				return;
			}
			s_GLFWInitialized = true;
		}

		// Window creation
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			// Handle window creation failure
			// You can log an error or throw an exception here.
			return;
		}
		//NOT RESIZABLE FOR NOW
		glfwSetWindowAttrib(m_Window, GLFW_RESIZABLE, GLFW_TRUE);

		glfwMakeContextCurrent(m_Window);
		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSwapInterval(1);

		//GLFW callbacks
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeEvent event(width, height);
			data.EventCallback(event);
			});
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseEvent event;
			data.EventCallback(event);

			});
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			UNREFERENCED_PARAMETER(scancode);
			UNREFERENCED_PARAMETER(mods);
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedEvent event(key, 0);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedEvent event(key);
				data.EventCallback(event);
				break;
			}
			case GLFW_REPEAT: {
				KeyPressedEvent event(key, 1);
				data.EventCallback(event);
				break;
			}
			}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			KeyTypedEvent event(keycode);
			data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
			UNREFERENCED_PARAMETER(mods);
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS: {
				MouseButtonPressedEvent event(button);
				data.EventCallback(event);
				break;
			}
			case GLFW_RELEASE: {
				MouseButtonReleasedEvent event(button);
				data.EventCallback(event);
				break;
			}
			}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseScrolledEvent event((float)xOffset, (float)yOffset);
			data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallback(event);
			});

		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* window, int focused) {
			WindowsWindow* wnd = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
			if (wnd) {
				Logger::GetInstance().Log(LogLevel::Info, "Window focus callback triggered");
				// Update focus state using GLFW function
				wnd->m_IsFocused = focused;
			}
			});

		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* window, int maximized) {
			WindowsWindow* wnd = static_cast<WindowsWindow*>(glfwGetWindowUserPointer(window));
			if (wnd) {
				Logger::GetInstance().Log(LogLevel::Info, "Window maximize callback triggered");
				wnd->m_IsMaximized = maximized;
			}
			});
	}

	/*!**********************************************************************
	\brief
	Shuts down the WindowsWindow, destroying the GLFW window.
	*************************************************************************/
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	/*!**********************************************************************
	\brief
	Updates the WindowsWindow by processing events and swapping buffers.
	*************************************************************************/
	void WindowsWindow::OnUpdate() {

		m_IsFocused = glfwGetWindowAttrib(m_Window, GLFW_FOCUSED) != 0;

		// Check if the window has lost focus and minimize if needed

		if (!m_IsFocused) {
			MinimizeWindow();
			audio.pauseAllAudio();
		}
		else {
			// Check if the window has gained focus and restore if needed
			if (m_IsMaximized) {
				RestoreWindow();
			}
			audio.resumeAllAudio();
		}
			
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::MinimizeWindow() {
		if (m_Window) {
			Logger::GetInstance().Log(LogLevel::Info, "Minimizing Window");
			glfwIconifyWindow(m_Window);
		}
	}

	void WindowsWindow::RestoreWindow() {
		if (m_Window) {
			Logger::GetInstance().Log(LogLevel::Info, "Restoring Window");
			glfwRestoreWindow(m_Window);
		}
	}
}