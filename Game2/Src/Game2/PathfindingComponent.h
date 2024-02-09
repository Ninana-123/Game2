/******************************************************************************/
/*!
\file		PathfindingComponent.h
\author		Ang Jun Sheng Aloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		30/10/2023
\brief		Contains the interface of the Physics Component

 */
 /******************************************************************************/
#ifndef ENGINE_PATHFINDINGCOMPONENT_H
#define ENGINE_PATHFINDINGCOMPONENT_H

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
		bool changedTowers = false;
		bool accessedCastle = false;
		std::vector<std::pair<int, int>> path; // Store the path as a list of points
		bool initialized = false;
		std::pair<int, int> previousPos1 = { 0, 0 };
		std::pair<int, int> previousPos2 = { 0, 0 };

		/*!
		\brief Get the type of the component.
		\return ComponentType::Pathfinding.
		*/
		ComponentType GetType() const override { return ComponentType::Pathfinding; }

		/*!
		\brief Clone the PathfindingComponent.
		\return A new instance of PathfindingComponent with copied values.
		*/
		Component* Clone() const override
		{
			PathfindingComponent* cloneComponent = new PathfindingComponent();
			cloneComponent->startX = startX;
			cloneComponent->startY = startY;
			cloneComponent->goalX = goalX;
			cloneComponent->goalY = goalY;
			cloneComponent->changedTowers = changedTowers;
			cloneComponent->accessedCastle = accessedCastle;
			cloneComponent->path = path;
			cloneComponent->initialized = initialized;
			cloneComponent->previousPos1 = previousPos1;
			cloneComponent->previousPos2 = previousPos2;
			return cloneComponent;
		}

		/*!
		\brief Serialize the component to an output stream.
		\param outputStream The output stream to write the serialized data to.
		*/
		void Serialize(std::ostream& outputStream) const override {
			outputStream << "startX: " << startX << '\n';
			outputStream << "startY: " << startY << '\n';
			outputStream << "goalX: " << goalX << '\n';
			outputStream << "goalY: " << goalY << '\n';
			outputStream << "initialized: " << initialized << '\n';
			//outputStream << "path: " << path.x << ' ' << path.y << '\n';
		}

		/*!
	   \brief Deserialize the component from an input stream.
	   \param inputStream The input stream to read the serialized data from.
	   */
		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			//int buffer;
			inputStream >> temp >> startX;
			inputStream >> temp >> startY;
			inputStream >> temp >> goalX;
			inputStream >> temp >> goalY;
			inputStream >> temp >> initialized;
			//inputStream >> temp >> buffer;
			//initialized = static_cast <bool>(buffer);
			//inputStream >> temp >> path.x >> path.y; 
		}
	};
}
#endif ENGINE_PATHFINDINGCOMPONENT_H