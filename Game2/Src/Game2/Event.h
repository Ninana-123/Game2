/******************************************************************************/
/*!
\file		Event.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Defines event-related classes and enums for the Game2 Engine.
            This file contains the declaration of event-related classes, enums,
            and macros.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_EVENT_H
#define ENGINE_EVENT_H

#include "pch.h"
#include "Core.h"
#include "Logger.h"

namespace Engine {

    /*!
    \enum EventType
    \brief Enum for different event types.
    */
    enum class EventType {
        None = 0,
        WindowClose, WindowResize, WindowFocus, WindowMoved,
        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    /*!
    \enum EventCategory
    \brief Enum for different event categories.
    */
    enum EventCategory {
        None = 0,
        EventCategoryApplication = BIT(0),
        EventCategoryInput = BIT(1),
        EventCategoryKeyboard = BIT(2),
        EventCategoryMouse = BIT(3),
        EventCategoryMouseButton = BIT(4)
    };

    /*!
    \def EVENT_CLASS_TYPE(type)
    \brief Macro to define event type and related functions.
    */
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type;}\
                               virtual EventType GetEventType() const override {return GetStaticType();}\
                               virtual const char* GetName() const override {return #type; }

    /*!
    \def EVENT_CLASS_CATEGORY(category)
    \brief Macro to define event category.
    */
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

    /*!
    \class Event
    \brief Base event class providing common functionality for derived event classes.
    */
    class GAME2_API Event
    {
        friend class EventDispatcher;
    public:
        // Functions to be implemented by derived event classes

        /*!
        \brief
        Gets the event type.

        \return
        The event type.
        */
        virtual EventType GetEventType() const = 0;

        /*!
        \brief
        Gets the name of the event.

        \return
        The name of the event.
        */
        virtual const char* GetName() const = 0;

        /*!
        \brief
        Gets the category flags of the event.

        \return
        The category flags of the event.
        */
        virtual int GetCategoryFlags() const = 0;

        /*!
        \brief
        Converts the event information to a string.

        \return
        A string representing the event information.
        */
        virtual std::string ToString() const { return GetName(); }

        /*!
        \brief
        Logs information about the event.
        */
        virtual void LogEventInfo() const = 0;

        /*!
        \brief
        Checks if the event has been handled.

        \note
        This is for internal use and should not be called directly.

        \return
        True if the event has been handled, false otherwise.
        */
        inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }
    protected:
        bool m_Handled = false; //!< Flag indicating whether the event has been handled.
    };

    /*!
    \class EventDispatcher
    \brief Event dispatcher to handle event functions.
    */
    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;
    public:

        /*!
        \brief
        Constructor for the EventDispatcher.

        \param event
        The event to be dispatched.
        */
        EventDispatcher(Event& event) : m_Event(event)
        {
        }

        /*!
        \brief
        Dispatches event function based on event type.

        \tparam T
        The type of the event.

        \param func
        The event function to be dispatched.

        \return
        True if the event function is dispatched successfully, false otherwise.
        */
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
        Event& m_Event; //!< The event to be dispatched.
    };

    /*!
    \brief
    Operator to print event to an output stream.

    \param os
    The output stream.

    \param e
    The event to be printed.

    \return
    The output stream after printing the event.
    */
    inline std::ostream& operator<<(std::ostream& os, const Event& e) {
        return os << e.ToString();
    }
}
#endif ENGINE_EVENT_H