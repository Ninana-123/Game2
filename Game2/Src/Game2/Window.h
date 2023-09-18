#pragma once

#include "pch.h"
#include "Core.h"
#include "Event.h"


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
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		static Window* Create(const WindowProps& props = WindowProps());
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void* GetNativeWindow() const = 0;
	};
}