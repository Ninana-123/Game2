#pragma once
/******************************************************************************/
/*!
\file		CollisionComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		27/09/2023
\brief		Contains the interface of the Collision Component

 */
 /******************************************************************************/
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
		float circleRadius = 0.0f;
		CollisionSystem::AABB aabb;

		int minX = 0;
		int minY = 0;
		int	maxX = 0;
		int	maxY = 0;

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
			cloneComponent->isColliding = isColliding;
			cloneComponent->circleRadius = circleRadius;
			cloneComponent->aabb.min.x = aabb.min.x;
			cloneComponent->aabb.max.x = aabb.max.x;
			cloneComponent->aabb.min.y = aabb.min.y;
			cloneComponent->aabb.max.y = aabb.max.y;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "c_Width: " << c_Width << '\n';
			outputStream << "c_Height: " <<  c_Height << '\n';
			outputStream << "isColliding: " << isColliding << '\n';
			//outputStream << "circleRadius: " << circleRadius << '\n';
			outputStream << "MinX: " << aabb.min.x << '\n';
			outputStream << "MinY: " << aabb.min.y << '\n';
			outputStream << "MaxX: " << aabb.max.x << '\n';
			outputStream << "MaxY: " << aabb.max.y << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> c_Width;
			inputStream >> temp >> c_Height;
			inputStream >> temp >> isColliding;
			//inputStream >> temp >> circleRadius;
			inputStream >> temp >> aabb.min.x;
			inputStream >> temp >> aabb.min.y;
			inputStream >> temp >> aabb.max.x;
			inputStream >> temp >> aabb.max.y;
		}

	};
}