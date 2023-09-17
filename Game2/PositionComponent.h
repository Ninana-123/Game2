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

		ComponentType GetType() const override { return ComponentType::Position; }
		Component* Clone() const override 
		{ 
			PositionComponent* cloneComponent = new PositionComponent;
			cloneComponent->position = position;
			return cloneComponent;
		}
	};
}