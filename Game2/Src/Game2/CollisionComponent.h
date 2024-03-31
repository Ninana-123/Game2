/******************************************************************************/
/*!
\file		CollisionComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		27/09/2023
\brief		Contains the interface of the Collision Component

 */
 /******************************************************************************/
#ifndef ENGINE_COLLISIONCOMPONENT_H
#define ENGINE_COLLISIONCOMPONENT_H

#include "Component.h"
#include "CollisionSystem.h"

namespace Engine
{
	class CollisionComponent : public Component
	{
	public:
		
		float c_Width = 0.0f;
		float c_Height = 0.0f;
		float arrowSpawnInterval = 2.0;
		float arrowSpawnTimer = arrowSpawnInterval;
		bool isColliding = false;
		bool mColliding = false;
		bool disableCollision = false;
		bool isArrow = false;
		bool towerShooting = false;
		bool arrowSpawned = false;
		CollisionSystem::AABB aabb;
		CollisionSystem::Circle circle;
		Layer layer = Layer::World;
		Entity* target = nullptr;
		VECTORMATH::Vector2D collisionVel = VECTORMATH::Vector2D(0.f, 0.f);
		std::queue<std::pair<EntityID, EntityID>> PlayerTowerQueue;
		std::vector<std::pair<EntityID, EntityID>> PlayerTowerVector;


		/*!*****************************************************************

		\brief
		Getter for this Components enum
	
		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Collision; }

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			CollisionComponent* cloneComponent = new CollisionComponent();
			cloneComponent->c_Width = c_Width;
			cloneComponent->c_Height = c_Height;
			cloneComponent->arrowSpawnInterval = arrowSpawnInterval;
			cloneComponent->arrowSpawnTimer = arrowSpawnTimer;
			cloneComponent->isColliding = isColliding;
			cloneComponent->aabb.min.x = aabb.min.x;
			cloneComponent->aabb.max.x = aabb.max.x;
			cloneComponent->aabb.min.y = aabb.min.y;
			cloneComponent->aabb.max.y = aabb.max.y;
			cloneComponent->circle.radius = circle.radius;
			cloneComponent->layer      = layer;
			cloneComponent->collisionVel = collisionVel;
			cloneComponent->PlayerTowerQueue = PlayerTowerQueue;
			cloneComponent->PlayerTowerVector = PlayerTowerVector;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "c_Width: " << c_Width << '\n';
			outputStream << "c_Height: " <<  c_Height << '\n';
			outputStream << "isColliding: " << isColliding << '\n';
			outputStream << "MinX: " << aabb.min.x << '\n';
			outputStream << "MinY: " << aabb.min.y << '\n';
			outputStream << "MaxX: " << aabb.max.x << '\n';
			outputStream << "MaxY: " << aabb.max.y << '\n';
			outputStream << "Radius: " << circle.radius << '\n';
			outputStream << "Layer: " << static_cast<int>(layer) << '\n';
			outputStream << "CollisionVel: " << collisionVel.x << ' ' << collisionVel.y << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			int buffer;
			inputStream >> temp >> c_Width;
			inputStream >> temp >> c_Height;
			inputStream >> temp >> isColliding;
			inputStream >> temp >> aabb.min.x;
			inputStream >> temp >> aabb.min.y;
			inputStream >> temp >> aabb.max.x;
			inputStream >> temp >> aabb.max.y;
			inputStream >> temp >> circle.radius;
			inputStream >> temp >> buffer;
			layer = static_cast<Layer>(buffer);
			inputStream >> temp >> collisionVel.x >> collisionVel.y;
		}
	};
}
#endif ENGINE_COLLISIONCOMPONENT_H