#pragma once

#include "Game2/Component.h"
#include "Game2/EngineTypes.h"


namespace Engine
{
	class PositionComponent : public Component
	{
	public:
		int x = 0, y = 0;

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