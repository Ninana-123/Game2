#include "pch.h"
#include "EntityManager.h"
#include "System.h"
#include "SystemsManager.h"
#include "Graphics.h"

namespace Engine
{
	EntityID EntityManager::nextEntityID = 0;

	EntityManager::~EntityManager()
	{

	}

	EntityID EntityManager::CreateEntity()
	{
		EntityID entityID = nextEntityID++;
		entities.emplace(entityID, std::make_unique<Entity>(entityID));
		return entityID;
	}

	EntityID EntityManager::CreateEntityFromPrefab(const Prefab& prefab)
	{
		EntityID newEntityID = CreateEntity();
		auto sourceComponents = prefab.GetComponents();

		// Copy components from the archetype to the new entity
		for (const auto& pair : sourceComponents)
		{
			ComponentType componentType = pair.first;
			Component* sourceComponent = pair.second;

			// Clone the component and add it to the entity using AddComponent
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes
			GetEntity(newEntityID)->AddComponent(std::unique_ptr<Component>(clonedComponent));
		}

		return newEntityID;
	}

	Entity* EntityManager::GetEntity(EntityID id) 
	{
		auto it = entities.find(id);
		return (it != entities.end()) ? it->second.get() : nullptr;
	}

	std::unordered_map<EntityID, std::unique_ptr<Entity>>* EntityManager::GetEntities()
	{
		return &entities;
	}

	EntityID EntityManager::CloneEntity(EntityID sourceEntityID) {
		// Get the source entity to clone
		Entity* sourceEntity = GetEntity(sourceEntityID);
		if (!sourceEntity) 
		{
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
			// After removing the entity, reassign EntityIDs to close gaps
			for (auto& pair : entities)
			{
				if (pair.first > entity) //check if ID is greater than the target ID
				{
					EntityID newID = pair.first - 1; // -1 and reassign entity ptr in map
					entities[newID] = std::move(pair.second);
					entities.erase(pair.first);
					pair.second->id = newID;
				}
			}
		}
	}
	
}

