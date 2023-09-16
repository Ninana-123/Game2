#pragma once

#include "Game2/Component.h"
#include "Game2/EngineTypes.h"
#include "glm/vec2.hpp"

namespace Engine
{
	class PositionComponent : public Component
	{
	public:
		glm::vec2 position;

		PositionComponent() : position(0.0, 0.0) { }
	};
}