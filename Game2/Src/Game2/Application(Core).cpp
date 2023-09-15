#include "pch.h"
#include "Application.h"
#include <GLFW/glfw3.h>

double fps = 0.00;
double previousTime = glfwGetTime();
int frameCount = 0;

namespace Engine
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));
		logger.Log(Engine::LogLevel::Event, e.ToString());
	}

	void Application::Run()
	{
		logger.Log(Engine::LogLevel::App, "Application Running.");
		
		while (m_Running) {
			m_Window->OnUpdate();
			//calculate fps
			double currentTime = glfwGetTime();
			double delta = currentTime - previousTime; // delta time
			frameCount++; // increment frame count
			if (delta >= 1.0) {
				fps = double(frameCount) / delta; // calculate fps
				frameCount = 0;
				previousTime = currentTime;
			}
			// Title
			std::stringstream ss;
			ss << std::fixed << std::setprecision(2) << fps;
			std::string fps_str = ss.str();
			std::string title_str = "Game2 | FPS: " + fps_str;
			glfwSetWindowTitle(glfwGetCurrentContext(), title_str.c_str());
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}
}