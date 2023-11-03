/******************************************************************************/
/*!
\file		AppEvent.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Declares event classes related to window actions for the Game2 
			Engine.
			This file contains the declaration of event classes for window 
			actions, such as resize and close.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "pch.h"
#include "Event.h"
#include "Logger.h"

namespace Engine {

	// Event for window resize
	class GAME2_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : Event(), m_Width(width), m_Height(height) {
			LogEventInfo(); // Log event information when the event is created
		}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		void LogEventInfo() const
		{
			Logger::GetInstance().Log(LogLevel::Event, "Event Type: " + ToString());
		}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize) // Set the event type
			EVENT_CLASS_CATEGORY(EventCategoryApplication) // Set the event category

	private:
		unsigned int m_Width, m_Height;
	};

	// Event for window close
	class GAME2_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() : Event() {}
		void LogEventInfo() const
		{
			// Log event information (to be implemented)
			Logger::GetInstance().Log(LogLevel::Event, "Event Type: " + ToString());
		}
		EVENT_CLASS_TYPE(WindowClose) // Set the event type
			EVENT_CLASS_CATEGORY(EventCategoryApplication) // Set the event category
	};
}
