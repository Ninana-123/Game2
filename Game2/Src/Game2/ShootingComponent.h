#pragma once
/******************************************************************************/
/*!
\file		ShootingComponent.h
\author		Tay Jun Feng Vance
\par		junfengvance.t@digipen.edu
\date		22/01/2024
\brief		Contains the interface of the Shooting Component

 */
 /******************************************************************************/
#include "Component.h"
#include "CollisionSystem.h"

namespace Engine
{
	class ShootingComponent : public Component
	{
	public:

		float cooldownTime; //Cooldown time between shots
		float timeSinceLastShot; //Time since the last shot
		float projectileSpeed; //Projectile speed
		int damage; //Damage dealt by projectile
		bool isShooting = false;

		/*!*****************************************************************

		\brief
		Getter for this Components enum
	
		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Shooting; }

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			ShootingComponent* cloneComponent = new ShootingComponent();
			cloneComponent->isShooting = isShooting;
			cloneComponent->cooldownTime = cooldownTime;
			cloneComponent->timeSinceLastShot = timeSinceLastShot;
			cloneComponent->projectileSpeed = projectileSpeed;
			cloneComponent->damage = damage;

			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "isShooting: " << isShooting << '\n';
			outputStream << "cooldownTime " << cooldownTime << '\n';
			outputStream << "timeSinceLastShot " << timeSinceLastShot << '\n';
			outputStream << "projectileSpeed " << projectileSpeed << '\n';
			outputStream << "damage " << damage << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			int buffer;
			inputStream >> temp >> isShooting;
			inputStream >> temp >> cooldownTime;
			inputStream >> temp >> timeSinceLastShot;
			inputStream >> temp >> projectileSpeed;
			inputStream >> temp >> damage;
		}
	};
}