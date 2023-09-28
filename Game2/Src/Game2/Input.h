#pragma once

#include "KeyCodes.h"
#include "MouseButtonCodes.h"
#include "Vector2d.h"
namespace Engine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
        bool IsKeyTriggered(const KeyCode key);
        bool IsKeyDown(const KeyCode key);
        bool IsKeyReleased(const KeyCode key);
        void UpdateKeyStates();
		void Update();
		static bool IsMouseButtonPressed(MouseCode button);
		static VECTORMATH::Vector2D GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}