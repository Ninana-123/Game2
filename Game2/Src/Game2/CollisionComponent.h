#pragma once
#include "Component.h"
#include "CollisionSystem.h"

namespace Engine
{
	class CollisionComponent : public Component
	{
	public:
		float c_Width = 0.0f;
		float c_Height = 0.0f;
		bool isColliding = false;

		int minX = 0;
		int minY = 0;
		int	maxX = 0;
		int	maxY = 0;

		ComponentType GetType() const override { return ComponentType::Collision; }
		Component* Clone() const override
		{
			CollisionComponent* cloneComponent = new CollisionComponent();
			cloneComponent->c_Width = c_Width;
			cloneComponent->c_Height = c_Height;
			cloneComponent->isColliding = isColliding;
			cloneComponent->minX = minX;
			cloneComponent->maxX = maxX;
			cloneComponent->minY = minY;
			cloneComponent->maxY = maxY;

			return cloneComponent;
		}
	};
}