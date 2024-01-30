/******************************************************************************/
/*!
\file		PhysicsComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		27/09/2023
\brief		Contains the interface of the Physics Component

 */
 /******************************************************************************/
#ifndef ENGINE_PHYSICSCOMPONENT_H
#define ENGINE_PHYSICSCOMPONENT_H

#include "Component.h"
#include "CollisionSystem.h"

namespace Engine
{
	class PhysicsComponent : public Component
	{
	public:
		
		VECTORMATH::Vector2D velocity = VECTORMATH::Vector2D(0.f, 0.f);
		VECTORMATH::Vector2D acceleration = VECTORMATH::Vector2D(0.f, 0.f);
		float mass = 0.0;
		float friction = 0.0;

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
			cloneComponent->acceleration = acceleration;
			cloneComponent->mass = mass;
			cloneComponent->friction = friction;
			
			return cloneComponent;
		}
		void Serialize(std::ostream& outputStream) const override {
			outputStream << "Velocity: " << velocity.x << ' ' << velocity.y << '\n';
			outputStream << "Acceleration: " << acceleration.x << ' ' << acceleration.y << '\n';
			outputStream << "Mass: " << mass << '\n';
			outputStream << "friction: " << friction << '\n';
		}
		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> velocity.x >> velocity.y; // Assuming format is "Position: x y"
			inputStream >> temp >> acceleration.x >> acceleration.y;
			inputStream >> temp >> mass;
			inputStream >> temp >> friction;
		}
	};
}
#endif ENGINE_PHYSICSCOMPONENT_H