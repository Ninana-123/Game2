#pragma once

#include "Game2/Window.h"

#include <GLFW/glfw3.h>

namespace Engine {
	class WindowsWindow : public Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate();

		inline unsigned int GetWidth() const { return m_Data.Width; }
		inline unsigned int GetHeight() const { return m_Data.Height; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
		struct WindowData {
			std::string Title;
			unsigned int Width, Height;
		};
		WindowData m_Data;
	};
}