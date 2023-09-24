#pragma once

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{

	class PositionComponent : public Component
	{
	public:
		int x = 10, y = 15;

		ComponentType GetType() const override { return ComponentType::Position; }
		Component* Clone() const override 
		{ 
			PositionComponent* cloneComponent = new PositionComponent();
			cloneComponent->x = x;
			cloneComponent->y = y;
			return cloneComponent;
		}
	};
}