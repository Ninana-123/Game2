#pragma once

#include "KeyCodes.h"
#include "MouseButtonCodes.h"

#include <glm/glm.hpp>

namespace Engine {

	class Input
	{
	public:
		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);
		static glm::vec2 GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}