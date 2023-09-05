#pragma once

#include "pch.h"
#include "Game2/Core.h"

namespace Engine {
	struct WindowProps {
		std::string Title;
		unsigned int Width;
		unsigned int Height;

		WindowProps(const std::string& title = "Game2 Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {
		}
	};
	class GAME2_API Window{
	public:
		virtual ~Window() {}
		static Window* Create(const WindowProps& props = WindowProps());
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;

	};
}