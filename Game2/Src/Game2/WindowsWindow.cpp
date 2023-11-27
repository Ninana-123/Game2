/******************************************************************************/
/*!
\file		WindowsWindow.cpp
\author 	Liu Xujie
\co			Kwok Jun Lin Wayne (20%)
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
	AudioEngine audio;

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

	// Factory method to create a new WindowsWindow
	Window* Window::Create(const WindowConfig& props) {
		return new WindowsWindow(props);
	}

	// Constructor for the WindowsWindow class
	WindowsWindow::WindowsWindow(const WindowConfig& props) {
		Init(props);
	}

	// Destructor for the WindowsWindow class
	WindowsWindow::~WindowsWindow() {
		// Perform any necessary cleanup
	}

	// Initialize the WindowsWindow using provided WindowConfig properties
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

		//const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
		//m_Window = glfwCreateWindow(mode->width, mode->height, m_Data.Title.c_str(), glfwGetPrimaryMonitor(), nullptr);
		//glfwSetWindowMonitor(GetNativeWindow(), glfwGetPrimaryMonitor(), 0, 0, mode->width, mode->height, mode->refreshRate);

	#ifdef DEBUG
		
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		if (!m_Window) {
			// Handle window creation failure
			// You can log an error or throw an exception here.
			return;
		}

		//NOT RESIZABLE FOR NOW
	#else
		GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();
		if (!primaryMonitor) {
			Logger::GetInstance().Log(LogLevel::Error, "Failed to get primary monitor.");
			return;
		}
		const GLFWvidmode* mode = glfwGetVideoMode(primaryMonitor);
		if (!mode) {
			Logger::GetInstance().Log(LogLevel::Error, "Failed to get video mode for primary monitor.");
			return;
		}
		m_Window = glfwCreateWindow(mode->width, mode->height, m_Data.Title.c_str(), primaryMonitor, nullptr);
	#endif
		
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
				// Update focus state using GLFW function only if not interacting with ImGui
				if (!wnd->IsImGuiHovered()) {
					wnd->m_IsFocused = focused;
				}
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

	// Shutdown the WindowsWindow, destroying the GLFW window
	void WindowsWindow::Shutdown() {
		glfwDestroyWindow(m_Window);
	}

	// Update the WindowsWindow by processing events and swapping buffers
	void WindowsWindow::OnUpdate() {


		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	// Minimize the window
	void WindowsWindow::MinimizeWindow() {
		if (m_Window) {
			Logger::GetInstance().Log(LogLevel::Info, "Minimizing Window");

			// Iconify (minimize) the GLFW window
			glfwIconifyWindow(m_Window);
			m_IsMaximized = false;
			//audio.pauseAllAudio();
		}
	}

	// Restore the window
	void WindowsWindow::RestoreWindow() {
		if (m_Window) {
			// Log information
			Logger::GetInstance().Log(LogLevel::Info, "Restoring Window");

			// Restore the GLFW window
			glfwRestoreWindow(m_Window);
		}
	}

	void WindowsWindow::SwitchToWindowedMode()
	{
		// Check if the window is not already in windowed mode
		if (!glfwGetWindowMonitor(m_Window))
		{
			// Get the current window position and size
			int x, y, width, height;
			glfwGetWindowPos(m_Window, &x, &y);
			glfwGetWindowSize(m_Window, &width, &height);

			// Restore the windowed mode with the previous position and size
			glfwSetWindowMonitor(m_Window, nullptr, x, y, width, height, 0);
		}
	}

	void WindowsWindow::SwitchToFullScreenMode()
	{
		// Check if the window is not already in full-screen mode
		if (!glfwGetWindowMonitor(m_Window))
		{
			// Get the primary monitor
			GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

			// Get the current window position and size
			int x, y, width, height;
			glfwGetWindowPos(m_Window, &x, &y);
			glfwGetWindowSize(m_Window, &width, &height);

			// Switch to full-screen mode using the primary monitor
			glfwSetWindowMonitor(m_Window, primaryMonitor, 0, 0, width, height, GLFW_DONT_CARE);
		}
		else
		{
			// If the window is already in full-screen mode, switch to windowed mode
			SwitchToWindowedMode();
		}
	}
} // namespace Engine