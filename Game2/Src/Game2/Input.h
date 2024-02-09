/******************************************************************************/
/*!
\file		Input.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Declares the Input class and related functionalities for keyboard 
			and mouse input handling.
			This file contains the declaration of the Input class and 
			associated methods for managing keyboard and mouse input.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#ifndef ENGINE_INPUT_H
#define ENGINE_INPUT_H

#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Vector2d.h"
#include "EntityManager.h"
#include "ImGuiWrapper.h"

namespace Engine {

	class Input
	{
	public:
        /*!
            * \brief Checks if the specified keyboard key is currently pressed.
            *
            * \param key Key code of the keyboard key to check.
            * \return True if the key is currently pressed, false otherwise.
            */
        static bool IsKeyPressed(KeyCode key);

        /*!
         * \brief Checks if the specified keyboard key is triggered (pressed with a cooldown).
         *
         * \param key Key code of the keyboard key to check.
         * \return True if the key is currently triggered, false otherwise.
         */
        static bool IsKeyTriggered(const KeyCode key);

        /*!
         * \brief Checks if the specified keyboard key is currently down (pressed).
         *
         * \param key Key code of the keyboard key to check.
         * \return True if the key is currently down, false otherwise.
         */
        static bool IsKeyDown(const KeyCode key);

        /*!
         * \brief Checks if the specified keyboard key is released.
         *
         * \param key Key code of the keyboard key to check.
         * \return True if the key is released, false otherwise.
         */
        static bool IsKeyReleased(const KeyCode key);

        /*!
         * \brief Updates the previous key states with the current key states.
         */
        void UpdateKeyStates();

        /*!
         * \brief Updates the key states based on the current state of each key.
         */
        void Update();

        /*!
         * \brief Checks if the specified mouse button is currently pressed.
         *
         * \param button The mouse button to check.
         * \return True if the mouse button is pressed, false otherwise.
         */
        static bool IsMouseButtonPressed(MouseCode button);

        /*!
         * \brief Checks if the specified mouse button is released.
         *
         * \param button The mouse button to check.
         * \return True if the mouse button is released, false otherwise.
         */
        static bool IsMouseButtonReleased(const MouseCode button);

        /*!
         * \brief Checks if the specified mouse button is clicked.
         *
         * \param button The mouse button to check.
         * \return True if the mouse button is clicked, false otherwise.
         */
        static bool IsMouseClicked(const MouseCode button);

        /*!
         * \brief Gets the current mouse position.
         *
         * \return The mouse position as a Vector2D.
         */
        static VECTORMATH::Vector2D GetMousePosition();

        /*!
         * \brief Gets the current mouse X position.
         *
         * \return The mouse X position.
         */
        static float GetMouseX();

        /*!
         * \brief Gets the current mouse Y position.
         *
         * \return The mouse Y position.
         */
        static float GetMouseY();

        /*!
         * \brief Gets the current mouse delta X position.
         *
         * \return The mouse delta X position.
         */
        float GetMouseDeltaX() const;

        /*!
         * \brief Gets the current mouse scroll delta.
         *
         * \return The mouse scroll delta.
         */
        float GetMouseScrollDelta() const;

        /*!
         * \brief Sets the EntityManager for input-related operations.
         *
         * \param manager A shared pointer to the EntityManager.
         */
        void SetEntityManager(std::shared_ptr<Engine::EntityManager> manager);

        /*!
         * \brief Sets the ImGuiWrapper for input-related operations.
         *
         * \param imGui A shared pointer to the ImGuiWrapper.
         */
        void SetImGuiWrapper(std::shared_ptr<Engine::ImGuiWrapper> imGui);

        /*!
         * \brief Performs picking operation based on mouse input.
         */
        void Picking();

        /*!
         * \brief Performs dragging operation based on mouse input.
         */
        void Dragging();

        /*!
         * \brief Performs deletion operation based on mouse input.
         */
        void Delete();

        //void Undo(); // Uncomment this line if the Undo function is implemented.

	private:
		std::shared_ptr<EntityManager> entityManager;
		std::shared_ptr<ImGuiWrapper> ImGuiWrapper;
		EntityID targetEntityID = static_cast<EntityID>(-1);
		bool isDragging = false;
	};
}
#endif ENGINE_INPUT_H