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
#pragma once

#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Vector2d.h"
#include "EntityManager.h"

namespace Engine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
        static bool IsKeyTriggered(const KeyCode key);
        bool IsKeyDown(const KeyCode key);
        bool IsKeyReleased(const KeyCode key);
		void UpdateKeyStates();
		void Update();
		static bool IsMouseButtonPressed(MouseCode button);
		static VECTORMATH::Vector2D GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
		float GetMouseDeltaX() const;
		float GetMouseScrollDelta() const;

		void SetEntityManager(std::shared_ptr<Engine::EntityManager> manager);
		void Picking();
	private:
		std::shared_ptr<EntityManager> entityManager;
	};
}