#pragma once

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{

	class TransformComponent : public Component
	{
	public:
		int x = 0, y = 0;
		float scaleX = 1.0f, scaleY = 1.0f;
		float rot = 0.0f;

		ComponentType GetType() const override { return ComponentType::Transform; }
		Component* Clone() const override
		{
			TransformComponent* cloneComponent = new TransformComponent();
			cloneComponent->x = x;
			cloneComponent->y = y;
			return cloneComponent;
		}
	};
}