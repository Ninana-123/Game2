#pragma once
/******************************************************************************/
/*!
\file		PhysicsComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		27/09/2023
\brief		Contains the interface of the Physics Component

 */
 /******************************************************************************/

#include "Component.h"
#include "CollisionSystem.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		
		float velocityX = 0.0f;
		float velocityY = 0.0f;

		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Physics; }

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			PhysicsComponent* cloneComponent = new PhysicsComponent();
			cloneComponent->velocityX = velocityX;
			cloneComponent->velocityY = velocityY;
			
			return cloneComponent;
		}
	};
}