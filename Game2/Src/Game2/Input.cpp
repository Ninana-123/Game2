/******************************************************************************/
/*!
\file		Input.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Implements the Input class methods for handling keyboard and mouse 
            input.
            This file contains the implementation of methods in the Input 
            class to handle keyboard and mouse input.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "Input.h"
#include "Application.h"
#include <GLFW/glfw3.h>

namespace Engine {

    // Static variables to store the key states and related data
    static std::unordered_map<KeyCode, bool> s_KeyState;  // Current key states
    static std::unordered_map<KeyCode, bool> s_KeyStatePrev;  // Previous key states
    static std::unordered_map<KeyCode, std::chrono::steady_clock::time_point> s_KeyCooldown;  // Cooldown time for key triggers

    /*!**********************************************************************
    \brief
    Checks if the specified keyboard key is currently pressed.
    \param[in] key 
    key code of the keyboard key to check.
    \return 
    true if the key is currently pressed, false otherwise.
    *************************************************************************/
    bool Input::IsKeyPressed(const KeyCode key)
    {
        auto* window = glfwGetCurrentContext();
        auto state = glfwGetKey(window, static_cast<int32_t>(key));
        return state == GLFW_PRESS;
    }
    /*!**********************************************************************
    \brief
    Checks if the specified keyboard key is triggered (pressed with a cooldown).
    \param[in] key
    key code of the keyboard key to check.
    \return
    true if the key is currently triggered, false otherwise.
    *************************************************************************/
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
    /*!**********************************************************************
    \brief
    Checks if the specified keyboard key is currently down (pressed).
    \param[in] key
    key code of the keyboard key to check.
    \return
    true if the key is currently down, false otherwise.
    *************************************************************************/
    bool Input::IsKeyDown(const KeyCode key)
    {
        return IsKeyPressed(key);
    }
    /*!**********************************************************************
    \brief
    Checks if the specified keyboard key is released
    \param[in] key
    key code of the keyboard key to check.
    \return
    true if the key is released, false otherwise.
    *************************************************************************/
    bool Input::IsKeyReleased(const KeyCode key)
    {
        return !IsKeyPressed(key) && s_KeyStatePrev[key];
    }
    /*!**********************************************************************
    \brief
    Updates the previous key states with the current key states.
    *************************************************************************/
    void Input::UpdateKeyStates()
    {
        for (const auto& kvp : s_KeyState)
        {
            KeyCode key = kvp.first;
            s_KeyStatePrev[key] = kvp.second;
        }
    }
    /*!**********************************************************************
    \brief
    Updates the key states based on the current state of each key.
    *************************************************************************/
    void Input::Update()
    {
        // Update key states
        s_KeyState.clear();
        for (int32_t i = GLFW_KEY_SPACE; i <= GLFW_KEY_LAST; ++i)
        {
            s_KeyState[static_cast<KeyCode>(i)] = glfwGetKey(glfwGetCurrentContext(), i) == GLFW_PRESS;
        }
    }
    /*!**********************************************************************
    \brief
    Checks if the specified mouse button is currently pressed.
    \param[in] button 
    The mouse button to check.
    \return
    True if the mouse button is pressed, false otherwise.
    *************************************************************************/
    bool Input::IsMouseButtonPressed(const MouseCode button)
    {
        auto* window = glfwGetCurrentContext();
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_PRESS;
    }
    /*!**********************************************************************
    \brief
    Gets the current mouse position.
    \return
    The mouse position as a Vector2D.
    *************************************************************************/
    VECTORMATH::Vector2D Input::GetMousePosition()
    {
        auto* window = glfwGetCurrentContext();
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        return { (float)xpos, (float)ypos };
    }
    /*!**********************************************************************
    \brief
    Gets the current mouse X position.
    \return
    The mouse X position
    *************************************************************************/
    float Input::GetMouseX()
    {
        return GetMousePosition().x;
    }
    /*!**********************************************************************
    \brief
    Gets the current mouse Y position.
    \return
    The mouse Y position
    *************************************************************************/
    float Input::GetMouseY()
    {
        return GetMousePosition().y;
    }

}  // namespace Engine
