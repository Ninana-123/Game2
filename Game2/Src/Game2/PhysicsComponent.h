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
		
		VECTORMATH::Vector2D velocity = VECTORMATH::Vector2D(0.f, 0.f);

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
			cloneComponent->velocity = velocity;
			
			return cloneComponent;
		}
		void Serialize(std::ostream& outputStream) const override {
			outputStream << "Velocity: " << velocity.x << ' ' << velocity.y << '\n';
		}
		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> velocity.x >> velocity.y; // Assuming format is "Position: x y"
		}
	};
}