/******************************************************************************/
/*!
\file		EntityManager.cpp
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the definitions of the System Manager

 */
 /******************************************************************************/

#include "pch.h"
#include "EntityManager.h"
#include "System.h"
#include "SystemsManager.h"
#include "GraphicsSystem.h"

namespace Engine
{
	EntityID EntityManager::nextEntityID = 0;

	EntityID EntityManager::CreateEntity()
	{
		EntityID entityID = nextEntityID++;
		entities.emplace(entityID, std::make_unique<Entity>(entityID));
		return entityID;
	}

	EntityID EntityManager::CreateEntityFromPrefab(const Prefab& prefab)
	{
		EntityID newEntityID = CreateEntity();
		Entity* newEntity = GetEntity(newEntityID);
		auto sourceComponents = prefab.GetComponents();

		// Copy components from the archetype to the new entity
		for (const auto& pair : sourceComponents)
		{
			Component* sourceComponent = pair.second;
			// Clone the component and add it to the entity using AddComponent
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes
			// Handle special case for ScriptComponent
			ComponentType type = clonedComponent->GetType();
			if (type == ComponentType::Script)
			{
				ScriptComponent* scriptComponent = dynamic_cast<ScriptComponent*>(clonedComponent);
				scriptComponent->SetEntity(newEntityID);
				scriptComponent->InitializeScript();
				newEntity->AddComponent(std::unique_ptr<Component>(scriptComponent));
			}
			else
			{
				// For other components, just clone and add them
				if (sourceComponent)
				{
					Component* clonedComponent = sourceComponent->Clone();
					newEntity->AddComponent(std::unique_ptr<Component>(clonedComponent));
				}
			}			
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

	EntityID EntityManager::CloneEntity(EntityID sourceEntityID) 
	{
		// Get the source entity to clone
		Entity* sourceEntity = GetEntity(sourceEntityID);
		if (!sourceEntity) 
		{
			// Entity not found
			return UINT_MAX;
		}

		// Create a new entity as a clone
		EntityID clonedEntityID = CreateEntity();
		Entity* clonedEntity = GetEntity(clonedEntityID);

		// Clone the components from the source entity to the cloned entity
		auto sourceComponents = sourceEntity->GetComponents();
		for (const auto& pair : sourceComponents)
		{
			Component* sourceComponent = pair.second;
			// Clone the component and add it to the entity using AddComponent
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes
			// Handle special case for ScriptComponent
			ComponentType type = clonedComponent->GetType();
			if (type == ComponentType::Script)
			{
				ScriptComponent* scriptComponent = dynamic_cast<ScriptComponent*>(clonedComponent);
				scriptComponent->SetEntity(clonedEntityID);
				scriptComponent->InitializeScript();
				clonedEntity->AddComponent(std::unique_ptr<Component>(scriptComponent));
			}
			else
			{
				// For other components, just clone and add them
				if (sourceComponent)
				{
					Component* clonedComponent = sourceComponent->Clone();
					clonedEntity->AddComponent(std::unique_ptr<Component>(clonedComponent));
				}
			}
		}

		return clonedEntityID;
	}

	EntityID EntityManager::CloneEntity(Entity* sourceEntity) {
		// Get the source entity to clone
		if (!sourceEntity)
		{
			// Entity not found
			return UINT_MAX;
		}

		// Create a new entity as a clone
		EntityID clonedEntityID = CreateEntity();
		Entity* clonedEntity = GetEntity(clonedEntityID);

		// Clone the components from the source entity to the cloned entity
		auto sourceComponents = sourceEntity->GetComponents();
		for (const auto& pair : sourceComponents)
		{
			Component* sourceComponent = pair.second;
			// Clone the component and add it to the entity using AddComponent
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes
			// Handle special case for ScriptComponent
			ComponentType type = clonedComponent->GetType();
			if (type == ComponentType::Script)
			{
				ScriptComponent* scriptComponent = dynamic_cast<ScriptComponent*>(clonedComponent);
				scriptComponent->SetEntity(clonedEntityID);
				scriptComponent->InitializeScript();
				clonedEntity->AddComponent(std::unique_ptr<Component>(scriptComponent));
			}
			else
			{
				// For other components, just clone and add them
				if (sourceComponent)
				{
					Component* clonedComponent = sourceComponent->Clone();
					clonedEntity->AddComponent(std::unique_ptr<Component>(clonedComponent));
				}
			}
		}

		return clonedEntityID;
	}

	void EntityManager::DestroyEntity(EntityID entity)
	{
		auto it = entities.find(entity);
		if (it != entities.end())
		{
			entities.erase(it);

			// create a buffer to hold new entities
			std::unordered_map<EntityID, std::unique_ptr<Entity>> updatedEntities;

			// reassign IDs and populate the new map
			EntityID newID = 0;
			for (auto& pair : entities)
			{
				if (pair.first != entity)
				{
					pair.second->id = newID;
					updatedEntities[newID] = std::move(pair.second);
					++newID;
				}
			}

			// update original map with buffer map
			entities = std::move(updatedEntities);
		}
		EntityID entityID = nextEntityID--;
	}

	void EntityManager::AddToStorage(EntityID entityID)
	{
		storage.push_back(entityID);
	}

	void EntityManager::RemoveFromStorage(EntityID entityID)
	{
		auto it = std::find(storage.begin(), storage.end(), entityID);
		if (it != storage.end()) {
			storage.erase(it);
		}
	}

	void EntityManager::DestroyEntitiesInStorage()
	{
		for(EntityID entityID : storage) {
			DestroyEntity(entityID);
		}
		storage.clear();
	}
}