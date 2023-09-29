#include "pch.h"
#include "Input.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Engine {
    static std::unordered_map<KeyCode, bool> s_KeyState;
    static std::unordered_map<KeyCode, bool> s_KeyStatePrev;
    static std::unordered_map<KeyCode, std::chrono::steady_clock::time_point> s_KeyCooldown;

    bool Input::IsKeyPressed(const KeyCode key)
    {
        auto* window = glfwGetCurrentContext();
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }

    bool Input::IsKeyTriggered(const KeyCode key)
    {
        auto currentTime = std::chrono::steady_clock::now();
        auto cooldownIt = s_KeyCooldown.find(key);

        if (IsKeyPressed(key) &&
            (cooldownIt == s_KeyCooldown.end() ||
                std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - cooldownIt->second).count() >= 500)) {
            // Update the cooldown time for the key
            s_KeyCooldown[key] = currentTime;
            return true;
        }

        return false;
    }

    bool Input::IsKeyDown(const KeyCode key)
    {
        return IsKeyPressed(key);
    }

    bool Input::IsKeyReleased(const KeyCode key)
    {
        return !IsKeyPressed(key) && s_KeyStatePrev[key];
    }

    void Input::UpdateKeyStates()
    {
        for (const auto& kvp : s_KeyState)
        {
            KeyCode key = kvp.first;
            s_KeyStatePrev[key] = kvp.second;
        }
    }

    void Input::Update()
    {
        // Update key states
        s_KeyState.clear();
        for (int32_t i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
        {
            s_KeyState[static_cast<KeyCode>(i)] = glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS;
        }
    }

    bool Input::IsMouseButtonPressed(const MouseCode button)
    {
        auto* window = glfwGetCurrentContext();
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }

    VECTORMATH::Vector2D Input::GetMousePosition()
    {
        auto* window = glfwGetCurrentContext();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }

    float Input::GetMouseX()
    {
        return GetMousePosition().x;
    }

    float Input::GetMouseY()
    {
        return GetMousePosition().y;
    }
}
