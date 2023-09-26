#pragma once

#include "pch.h"
#include "Core.h"
#include "Logger.h"

namespace Engine {

    // Enum for event types
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    // Enum for event categories
    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    // Macro to define event type and related functions
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type;}\
                               virtual EventType GetEventType() const override {return GetStaticType();}\
                               virtual const char* GetName() const override {return #type; }

    // Macro to define event category
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

    // Base event class
    class GAME2_API Event
    {
        friend class EventDispatcher;
    public:
        Event(Logger& logger) : m_Logger(logger) {}

        // Functions to be implemented by derived event classes
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }
        virtual void LogEventInfo() const = 0;

        inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    protected:
        Logger& m_Logger;
        bool m_Handled = false;
    };

    // Event dispatcher to handle event functions
    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:
        EventDispatcher(Event& event) : m_Event(event)
        {
        }

        // Dispatch event function based on event type
        template<typename T>
        bool Dispatch(EventFn<T> func) {
            if (m_Event.GetEventType() == T::GetStaticType())
            {
                m_Event.m_Handled = func(*(T*)&m_Event);
                return true;
            }
            else
                return false;
        }
    private:
        Event& m_Event;
    };

    // Operator to print event to an output stream
    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }
}
