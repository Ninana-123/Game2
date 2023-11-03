#pragma once
#include "Component.h"
#include "PathfindingSystem.h"
#include "EngineTypes.h"
#include "Vector2d.h"

namespace Engine
{
	class PathfindingComponent : public Component
	{
	public:
		int startX = 0; // Start point X
		int startY = 0; // Start point X
		int goalX = 0; // End point X
		int goalY = 0; // End point Y

		ComponentType GetType() const override { return ComponentType::Pathfinding; }

		Component* Clone() const override
		{
			PathfindingComponent* cloneComponent = new PathfindingComponent();
			cloneComponent->startX = startX;
			cloneComponent->startY = startY;
			cloneComponent->goalX= goalX;
			cloneComponent->goalY = goalY;
			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "startX: " << startX << '\n';
			outputStream << "startY: " << startY << '\n';
			outputStream << "goalX: " << goalX << '\n';
			outputStream << "goalY: " << goalY << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> startX;
			inputStream >> temp >> startY;
			inputStream >> temp >> goalX;
			inputStream >> temp >> goalY;
		}

	};
}