/******************************************************************************/
/*!
\file		Window.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Defines the abstract base class for a window in the Game2 Engine.
			This file contains the declaration of the Window class and 
			related structures.
 
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "pch.h"
#include "Core.h"
#include "Event.h"


namespace Engine {
	struct WindowConfig {
		std::string Title;
		unsigned int Width;
		unsigned int Height;
		//Default Properties
		WindowConfig(const std::string& title = "Game2 Engine",
			unsigned int width = 1280,
			unsigned int height = 720)
			: Title(title), Width(width), Height(height) {
		}

	};
	class GAME2_API Window{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}
		static Window* Create(const WindowConfig& props = WindowConfig());
		virtual void OnUpdate() = 0;

		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void* GetNativeWindow() const = 0;
	};
}