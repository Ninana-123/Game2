#pragma once
/******************************************************************************/
/*!
\file		ShootingSystem.h
\author		Tay Jun Feng Vance
\par		junfengvance.t@digipen.edu
\date		22/01/2024
\brief		Contains the declarations for shooting system class.

 */
 /******************************************************************************/
#include "ShootingComponent.h"
#include "System.h"

namespace Engine
{
	class ShootingSystem : public System
	{
		void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

		bool CanShoot(ShootingComponent* shootingComponent);

		void Shoot(ShootingComponent* shootingComponent);
	};
}