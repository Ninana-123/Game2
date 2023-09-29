#pragma once

#include "Window.h"
#include <GLFW/glfw3.h>

namespace Engine {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowConfig& props);
		virtual ~WindowsWindow();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		inline virtual void* GetNativeWindow() const { return m_Window; }

	private:
		virtual void Init(const WindowConfig& props);
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
	};
}