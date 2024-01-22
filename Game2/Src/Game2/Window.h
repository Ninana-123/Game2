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
#ifndef ENGINE_WINDOW_H
#define ENGINE_WINDOW_H

#include "pch.h"
#include "Core.h"
#include "Event.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>


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

        /*!
       ***********************************************************************
       \brief
       Factory method to create a Window object based on the
       provided WindowConfig properties.
       \param[in] props
       The WindowConfig containing the window properties.
       \return
       A pointer to the created Window object.
       ***********************************************************************/
        static Window* Create(const WindowConfig& props = WindowConfig());

        /*!
        ***********************************************************************
        \brief
        Pure virtual function to be implemented by derived classes.
        Updates the window, handling events, redraws, etc.
        ***********************************************************************/
        virtual void OnUpdate() = 0;

        /*!
        ***********************************************************************
        \brief
        Get the width of the window.
        \return
        The width of the window.
        ***********************************************************************/
        virtual unsigned int GetWidth() const = 0;

        /*!
        ***********************************************************************
        \brief
        Get the height of the window.
        \return
        The height of the window.
        ***********************************************************************/
        virtual unsigned int GetHeight() const = 0;

        /*!
        ***********************************************************************
        \brief
        Set the callback function to handle window events.
        \param[in] callback
        The callback function to be set.
        ***********************************************************************/
        virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

        /*!
        ***********************************************************************
        \brief
        Get the native window handle.
        \return
        A pointer to the native window handle.
        ***********************************************************************/
        virtual GLFWwindow* GetNativeWindow() const = 0;

    };
}
#endif ENGINE_WINDOW_H