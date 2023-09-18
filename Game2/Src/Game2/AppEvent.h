#pragma once

#include "pch.h"
#include "Event.h"

namespace Engine {

	// Event for window resize
	class GAME2_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(Logger& logger, unsigned int width, unsigned int height) : Event(logger), m_Width(width), m_Height(height) {
			LogEventInfo(); // Log event information when the event is created
		}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		void LogEventInfo() const
		{
			// Log event information (to be implemented)
			// This function can log event-specific details if needed
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
		WindowCloseEvent(Logger& logger) : Event(logger) {}
		void LogEventInfo() const
		{
			// Log event information (to be implemented)
			m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
		}
		EVENT_CLASS_TYPE(WindowClose) // Set the event type
			EVENT_CLASS_CATEGORY(EventCategoryApplication) // Set the event category
	};

	// Event for application tick
	class GAME2_API AppTickEvent : public Event {
	public:
		AppTickEvent(Logger& logger) : Event(logger) {}
		EVENT_CLASS_TYPE(AppTick) // Set the event type
			EVENT_CLASS_CATEGORY(EventCategoryApplication) // Set the event category
	};

	// Event for application update
	class GAME2_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent(Logger& logger) : Event(logger) {}
		EVENT_CLASS_TYPE(AppUpdate) // Set the event type
			EVENT_CLASS_CATEGORY(EventCategoryApplication) // Set the event category
	};

	// Event for application render
	class GAME2_API AppRenderEvent : public Event {
	public:
		AppRenderEvent(Logger& logger) : Event(logger) {}
		EVENT_CLASS_TYPE(AppRender) // Set the event type
			EVENT_CLASS_CATEGORY(EventCategoryApplication) // Set the event category
	};
}
