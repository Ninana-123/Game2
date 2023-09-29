#pragma once

#include "Component.h"
#include "CollisionSystem.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		
		float velocityX = 0.0f;
		float velocityY = 0.0f;

		ComponentType GetType() const override { return ComponentType::Collision; }
		Component* Clone() const override
		{
			PhysicsComponent* cloneComponent = new PhysicsComponent();
			cloneComponent->velocityX = velocityX;
			cloneComponent->velocityY = velocityY;
			
			return cloneComponent;
		}
	};
}