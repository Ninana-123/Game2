#include "EntityManager.h"

namespace Engine
{
	Engine::EntityManager::~EntityManager()
	{

	}

	EntityID Engine::EntityManager::CreateEntity()
	{
		EntityID entityID = nextEntityID++;
		entities.emplace(entityID, std::make_unique<Entity>(entityID));
		return entityID;
	}

	void Engine::EntityManager::DestroyEntity(EntityID entity)
	{
		auto it = entities.find(entity);
		if (it != entities.end()) 
		{
			entities.erase(it);
		}
	}

	void Engine::EntityManager::Update()
	{
		for (auto& entity : entities) 
		{
			entity.second->Update();
		}
	}
}

