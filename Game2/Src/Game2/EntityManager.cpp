#include "pch.h"
#include "EntityManager.h"
#include "System.h"
#include "SystemsManager.h"
#include "Graphics.h"

namespace Engine
{
	EntityID EntityManager::nextEntityID = 0;

	Engine::EntityManager::~EntityManager()
	{
	}

	EntityID Engine::EntityManager::CreateEntity()
	{
		EntityID entityID = nextEntityID++;
		entities.emplace(entityID, std::make_unique<Entity>(entityID));
		return entityID;
	}

	EntityID EntityManager::CreateEntityFromPrefab()
	{
		EntityID newEntityID = CreateEntity();
		return EntityID();
	}

	Entity* Engine::EntityManager::GetEntity(EntityID id) {
		auto it = entities.find(id);
		return (it != entities.end()) ? it->second.get() : nullptr;
	}

	EntityID Engine::EntityManager::CloneEntity(EntityID sourceEntityID) {
		// Get the source entity to clone
		Entity* sourceEntity = GetEntity(sourceEntityID);
		if (!sourceEntity) {
			// Entity not found
			return -1; // Or use an appropriate error value
		}

		// Create a new entity as a clone
		EntityID clonedEntityID = CreateEntity();
		Entity* clonedEntity = GetEntity(clonedEntityID);

		// Clone the components from the source entity to the cloned entity
		auto sourceComponents = sourceEntity->GetComponents();
		for (const auto& pair : sourceComponents) {
			ComponentType componentType = pair.first;
			Component* sourceComponent = pair.second;

			// You may need to implement a copy constructor or clone method for your components
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes

			// Add the cloned component to the cloned entity
			clonedEntity->AddComponent(std::unique_ptr<Component>(clonedComponent));
		}

		return clonedEntityID;
	}

	void Engine::EntityManager::DestroyEntity(EntityID entity)
	{
		auto it = entities.find(entity);
		if (it != entities.end()) 
		{
			entities.erase(it);
		}
	}
	void Engine::EntityManager::UpdateEntities()
	{
		for (const auto& entityPair : entities) 
		{
			Entity* entity = entityPair.second.get();
			//SystemsManager::UpdateSystems(entity);
			
		}
	}
}

