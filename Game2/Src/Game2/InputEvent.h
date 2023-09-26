#pragma once

#include "pch.h"
#include "Event.h"
#include "KeyCodes.h"
#include "MouseButtonCodes.h"

namespace Engine {

    // Keyboard Inputs

    // Base class for keyboard events
    class GAME2_API KeyEvent : public Event {
    public:
        inline KeyCode GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)

    protected:
        KeyEvent(Logger& logger, KeyCode keycode) : Event(logger), m_KeyCode(keycode) {}
        KeyCode m_KeyCode;
    };

    // Event for a key being pressed
    class GAME2_API KeyPressedEvent : public KeyEvent {
    public:
        KeyPressedEvent(Logger& logger, KeyCode keycode, int repeatCount) : KeyEvent(logger, keycode), m_RepeatCount(repeatCount) {}

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
            m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
        }
        EVENT_CLASS_TYPE(KeyPressed)

    private:
        int m_RepeatCount;
    };

    // Event for a key being released
    class GAME2_API KeyReleasedEvent : public KeyEvent {
    public:
        KeyReleasedEvent(Logger& logger, int keycode) : KeyEvent(logger, keycode) {}

        std::string ToString() const override {
            auto it = Engine::Key::keyMap.find(m_KeyCode);
            std::string keyName = (it != Key::keyMap.end()) ? it->second : "Unknown";
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << keyName;
            return ss.str();
        }
        void LogEventInfo() const
        {
            m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
        }
        EVENT_CLASS_TYPE(KeyReleased)
    };

    // Mouse Inputs

    // Event for mouse movement
    class GAME2_API MouseMovedEvent : public Event {
    public:
        MouseMovedEvent(Logger& logger, float x, float y) : Event(logger), m_MouseX(x), m_MouseY(y) {}

        inline float GetX() const { return m_MouseX; }
        inline float GetY() const { return m_MouseY; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
            return ss.str();
        }
        void LogEventInfo() const
        {
            m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
        }
        EVENT_CLASS_TYPE(MouseMoved)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_MouseX, m_MouseY;
    };

    // Event for mouse scroll
    class GAME2_API MouseScrolledEvent : public Event {
    public:
        MouseScrolledEvent(Logger& logger, float xOffset, float yOffset) : Event(logger), m_XOffset(xOffset), m_YOffset(yOffset) {}

        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << GetXOffset() << ", " << GetYOffset();
            return ss.str();
        }
        void LogEventInfo() const
        {
            m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
        }
        EVENT_CLASS_TYPE(MouseScrolled)
            EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    private:
        float m_XOffset, m_YOffset;
    };

    // Base class for mouse button events
    class GAME2_API MouseButtonEvent : public Event {
    public:
        inline int GetMouseButton() const { return m_Button; }

        EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    protected:
        MouseButtonEvent(Logger& logger, int button) : Event(logger), m_Button(button) {}

    private:
        int m_Button;
    };

    // Event for mouse button being pressed
    class GAME2_API MouseButtonPressedEvent : public MouseButtonEvent {
    public:
        MouseButtonPressedEvent(Logger& logger, int button) : MouseButtonEvent(logger, button) {}

        std::string ToString() const override {
            auto it = Engine::Mouse::mouseMap.find(GetMouseButton());
            std::string button = (it != Mouse::mouseMap.end()) ? it->second : "Unknown";
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << button;
            return ss.str();
        }
        void LogEventInfo() const
        {
            m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
        }
        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    // Event for mouse button being released
    class GAME2_API MouseButtonReleasedEvent : public MouseButtonEvent {
    public:
        MouseButtonReleasedEvent(Logger& logger, int button) : MouseButtonEvent(logger, button) {}

        std::string ToString() const override {
            auto it = Engine::Mouse::mouseMap.find(GetMouseButton());
            std::string button = (it != Mouse::mouseMap.end()) ? it->second : "Unknown";
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << button;
            return ss.str();
        }
        void LogEventInfo() const
        {
            m_Logger.Log(LogLevel::Event, "Event Type: " + ToString());
        }
        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
} // End of namespace Engine
