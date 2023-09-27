#pragma once

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

#include <glm/glm.hpp>

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
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}