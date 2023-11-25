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


    static float s_PrevMouseX = 0.0f;
    static float s_ScrollOffsetY = 0.0f;
    static float s_PrevScrollOffsetY = 0.0f;

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
        Picking();
        Dragging();
        Delete();
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

    bool Input::IsMouseButtonReleased(const MouseCode button)
    {
        auto* window = glfwGetCurrentContext();
        auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
        return state == GLFW_RELEASE;
    }

    bool Input::IsMouseClicked(MouseCode button)
    {
        static std::unordered_map<MouseCode, bool> prevMouseState;
        bool currentMouseState = IsMouseButtonPressed(button);

        // Check if the button was pressed in the current frame and released in the previous frame
        bool mouseClicked = currentMouseState && !prevMouseState[button];

        // Update the previous mouse state for the next frame
        prevMouseState[button] = currentMouseState;

        return mouseClicked;
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

    float Input::GetMouseDeltaX() const 
    {
        float currentMouseX = GetMouseX();
        float deltaX = currentMouseX - s_PrevMouseX;
        s_PrevMouseX = currentMouseX;  // Update the previous X position for the next frame
        return deltaX;
    }


    float Input::GetMouseScrollDelta() const
    {
        float deltaY = s_ScrollOffsetY - s_PrevScrollOffsetY;
        s_PrevScrollOffsetY = s_ScrollOffsetY;  // Update the previous scroll offset for the next frame
        return deltaY;
    }

    void Input::SetEntityManager(std::shared_ptr<Engine::EntityManager> manager)
    {
        entityManager = manager;
        if (!entityManager)
        {
            std::cout << "Failed to Link InputManager to EntityManager." << std::endl;
        }
    }

    void Input::SetImGuiWrapper(std::shared_ptr<Engine::ImGuiWrapper> ImGui)
    {
        ImGuiWrapper = ImGui;
        if (!ImGuiWrapper)
        {
            std::cout << "Failed to Link InputManager to ImGuiWrapper." << std::endl;
        }
    }

    void Input::Picking()
    {      
        if (IsMouseButtonPressed(LEFT_MOUSE_BUTTON))
        {
            //std::cout << "Picking Check. " << std::endl;           
            if (isDragging == false)
            {
                for (auto& entityPair : *(entityManager->GetEntities()))
                {
                    Entity* entity = entityPair.second.get();

                    // Check if the entity has a CollisionComponent
                    if (entity->HasComponent(ComponentType::Collision))
                    {
                        // Retrieve the CollisionComponent and TransformComponent
                        CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));

                        // Check if the entity is colliding with the mouse
                        if (collisionComponent->mColliding)
                        {
                            // Store the ID of the colliding entity
                            targetEntityID = entity->GetID();
                            ImGuiWrapper->SetTargetEntity(entityManager->GetEntity(targetEntityID));
                            //isDragging = true; // Start dragging mode                         
                            break; // Exit the loop after finding the first colliding entity
                        }
                        else
                        {
                            targetEntityID = -1;
                        }
                    }
                }
            }          
        }
        //std::cout << static_cast<int>(targetEntityID) << std::endl;
    }

    void Input::Dragging()
    {
        //target entity selected
        if (targetEntityID != -1)
        {
            if (IsMouseButtonPressed(LEFT_MOUSE_BUTTON))
            {         
                isDragging = true;

                Entity* DragEntity = entityManager->GetEntity(targetEntityID);

                VECTORMATH::Vector2D mousePosition = GetMousePosition();

                // Normalize the mouse position
                mousePosition.x -= 1270.0f / 2.0f;
                mousePosition.y = 720.0f / 2.0f - static_cast<float>(mousePosition.y);
               
                if (DragEntity && isDragging)
                {
                    CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(DragEntity->GetComponent(ComponentType::Collision));
                    TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(DragEntity->GetComponent(ComponentType::Transform));
                    transformComponent->position.x = mousePosition.x;
                    transformComponent->position.y = mousePosition.y;
                }
            }  
            else
            {
                isDragging = false;
            }
        }
    }

    void Input::Delete()
    {      
        
            if (IsKeyTriggered(KEY_DELETE))
            {
                Entity* deleteEntity = ImGuiWrapper->TargetEntityGetter();
                targetEntityID = deleteEntity->GetID();
                if (deleteEntity)
                {                                                                                  
                    if (targetEntityID >= 1)
                    {
                        std::cout << targetEntityID << std::endl;
                        entityManager->DestroyEntity(targetEntityID);
                        ImGuiWrapper->SetTargetEntity(entityManager->GetEntity(--targetEntityID));
                    }                   
                }
                else
                {
                    targetEntityID = -1;
                }             
            }             
    }

}  // namespace Engine
