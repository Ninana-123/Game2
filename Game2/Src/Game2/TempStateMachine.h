#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Entity.h"
#include "Component.h"
#include "AssetManager.h"

extern bool isGameOver;

namespace Engine
{
	class StateMachine
	{
	public:

		void UpdateEntities(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, AudioEngine& audioEngine, AssetManager& assetManager);

		void Idle(Entity* entity);

		void Walking(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager);

		void Attack(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager);

		void Death(Entity* entity);
	};
	
}
