/******************************************************************************/
/*!
\file		InputEvent.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Declares event classes related to input for the Game2 Engine.
This file contains the declaration of event classes for keyboard and mouse inputs.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_INPUTEVENTS_H
#define ENGINE_INPUTEVENTS_H

#include "pch.h"
#include "Event.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace Engine {

    // Keyboard Inputs

    /*!
     * \brief Base class for keyboard events.
     *
     * This class serves as the base class for keyboard events and provides common functionality.
     */
    class GAME2_API KeyEvent : public Event {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(KeyCode keycode) : Event(), m_KeyCode(keycode) {}
        KeyCode m_KeyCode;
    };

    /*!
     * \brief Event for a key being pressed.
     *
     * This class represents an event that occurs when a key is pressed.
     */
    class GAME2_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(KeyCode keycode, int repeatCount) : KeyEvent(keycode), m_RepeatCount(repeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }
        std::string ToString() const override {
            auto it = Engine::Key::keyMap.find(m_KeyCode);
            std::string keyName = (it != Key::keyMap.end()) ? it->second : "Unknown";
   
            std::stringstream ss;
            ss << "KeyPressedEvent: " << keyName << " ( " << m_RepeatCount << " repeats)";
            return ss.str();
        }

        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_RepeatCount;
    };

    /*!
     * \brief Event for a key being released.
     *
     * This class represents an event that occurs when a key is released.
     */
    class GAME2_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

        std::string ToString() const override {
            auto it = Engine::Key::keyMap.find(m_KeyCode);
            std::string keyName = (it != Key::keyMap.end()) ? it->second : "Unknown";
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << keyName;
            return ss.str();
        }
        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(KeyReleased)
    };

    /*!
     * \brief Event for a key being typed.
     *
     * This class represents an event that occurs when a key is typed.
     */
    class GAME2_API KeyTypedEvent : public KeyEvent {
    public:
        KeyTypedEvent(KeyCode keycode) : KeyEvent(keycode) {}
        std::string ToString() const override {
            auto it = Engine::Key::keyMap.find(m_KeyCode);
            std::string keyName = (it != Key::keyMap.end()) ? it->second : "Unknown";

            std::stringstream ss;
            ss << "KeyTypedEvent: " << keyName ;
            return ss.str();
        }
        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(KeyTyped)

    };
    // Mouse Inputs


    /*!
     * \brief Event for mouse movement.
     *
     * This class represents an event that occurs when the mouse is moved.
     */
    class GAME2_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(float x, float y) : Event(), m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }
        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_MouseX, m_MouseY;
    };

    /*!
     * \brief Event for mouse scroll.
     *
     * This class represents an event that occurs when the mouse is scrolled.
     */
    class GAME2_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(float xOffset, float yOffset) : Event(), m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }
        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_XOffset, m_YOffset;
    };

    /*!
     * \brief Base class for mouse button events.
     *
     * This class serves as the base class for mouse button events and provides common functionality.
     */
    class GAME2_API MouseButtonEvent : public Event {
    public:
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(int button) : Event(), m_Button(button) {}

    private:
        int m_Button;
    };

    /*!
      * \brief Event for mouse button being pressed.
      *
      * This class represents an event that occurs when a mouse button is pressed.
      */
    class GAME2_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(int button) : MouseButtonEvent(button), m_MouseX(0), m_MouseY(0) {}
        inline void SetX(float X) { m_MouseX = X; }
        inline void SetY(float Y) { m_MouseY = Y; }
        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            auto it = Engine::Mouse::mouseMap.find(GetMouseButton());
            std::string button = (it != Mouse::mouseMap.end()) ? it->second : "Unknown";
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << button;
            return ss.str();
        }
        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(MouseButtonPressed)
    private:
        float m_MouseX, m_MouseY;


    };

    /*!
     * \brief Event for mouse button being released.
     *
     * This class represents an event that occurs when a mouse button is released.
     */
    class GAME2_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}

        std::string ToString() const override {
            auto it = Engine::Mouse::mouseMap.find(GetMouseButton());
            std::string button = (it != Mouse::mouseMap.end()) ? it->second : "Unknown";
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << button;
            return ss.str();
        }
        void LogEventInfo() const
        {
            Logger::GetInstance().Log(LogLevel::Event, ("Event Type: " + ToString()).c_str());
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
} // End of namespace Engine
#endif ENGINE_INPUTEVENTS_H