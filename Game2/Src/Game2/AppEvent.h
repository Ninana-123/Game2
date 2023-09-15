#pragma once

#include "pch.h"
#include "Event.h"

namespace Engine {
	class GAME2_API WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(Logger& logger, unsigned int width, unsigned int height) : Event(logger), m_Width(width), m_Height(height) {
			LogEventInfo(); // Log event information when the event is created
		}
		inline unsigned int GetWidth() const { return m_Width; }
		inline unsigned int GetHeight() const { return m_Height; }
		void LogEventInfo() const
		{
		}
		std::string ToString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	private:
		unsigned int m_Width, m_Height;
	};

	class GAME2_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent(Logger& logger): Event(logger) {}
		void LogEventInfo() const
		{
			m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
		}
		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GAME2_API AppTickEvent : public Event {
	public:
		AppTickEvent(Logger& logger) : Event(logger) {}
		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GAME2_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent(Logger& logger) : Event(logger) {}
		EVENT_CLASS_TYPE(AppUpdate)
			EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class GAME2_API AppRenderEvent : public Event {
	public:
		AppRenderEvent(Logger& logger) : Event(logger) {}
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}