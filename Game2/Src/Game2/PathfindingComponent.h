#pragma once
/******************************************************************************/
/*!
\file		PathfindingComponent.h
\author		Ang Jun Sheng Aloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		30/10/2023
\brief		Contains the interface of the Physics Component

 */
 /******************************************************************************/
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
		std::vector<std::pair<int, int>> path; // Store the path as a list of points
		// bool initialized = false;

		ComponentType GetType() const override { return ComponentType::Pathfinding; }

		Component* Clone() const override
		{
			PathfindingComponent* cloneComponent = new PathfindingComponent();
			cloneComponent->startX = startX;
			cloneComponent->startY = startY;
			cloneComponent->goalX= goalX;
			cloneComponent->goalY = goalY;
			cloneComponent->path = path;
			//cloneComponent->initialized = initialized;
			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "startX: " << startX << '\n';
			outputStream << "startY: " << startY << '\n';
			outputStream << "goalX: " << goalX << '\n';
			outputStream << "goalY: " << goalY << '\n';
			//outputStream << "initialized: " << initialized << '\n';
			//outputStream << "path: " << path.x << ' ' << path.y << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			//int buffer;
			inputStream >> temp >> startX;
			inputStream >> temp >> startY;
			inputStream >> temp >> goalX;
			inputStream >> temp >> goalY;
			//inputStream >> temp >> buffer;
			//initialized = static_cast <bool>(buffer);
			//inputStream >> temp >> path.x >> path.y; 
		}

	};
}