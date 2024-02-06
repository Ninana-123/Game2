#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Entity.h"
#include "Component.h"

namespace Engine
{
	class StateMachine
	{
	public:
		
		void UpdateEntities(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

		void Idle(Entity* entity);

		void Walking(Entity* entity);

		void Attack(Entity* entity);

		void Death(Entity* entity);
	};
	
}
