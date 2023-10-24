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
			cloneComponent->minX = minX;
			cloneComponent->maxX = maxX;
			cloneComponent->minY = minY;
			cloneComponent->maxY = maxY;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "c_Width: " << c_Width << '\n';
			outputStream << "c_Height: " <<  c_Height << '\n';
			outputStream << "isColliding: " << isColliding << '\n';
			outputStream << "Min X: " << minX << '\n';
			outputStream << "Min Y: " << minY << '\n';
			outputStream << "Max X: " << maxX << '\n';
			outputStream << "Max Y: " << maxY << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> c_Width;
			inputStream >> temp >> c_Height;
			inputStream >> temp >> isColliding;
			inputStream >> temp >> minX;
			inputStream >> temp >> minY;
			inputStream >> temp >> maxX;
			inputStream >> temp >> maxY;
		}

	};
}