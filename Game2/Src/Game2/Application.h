#pragma once

#include "Core.h"
#include "Window.h"


namespace Engine
{
	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	Application* CreateApplication();

}