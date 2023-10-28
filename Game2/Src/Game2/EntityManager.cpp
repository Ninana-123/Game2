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
			UNREFERENCED_PARAMETER(componentType);
			UNREFERENCED_PARAMETER(sourceComponent);
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
			return UINT_MAX;
		}

		// Create a new entity as a clone
		EntityID clonedEntityID = CreateEntity();
		Entity* clonedEntity = GetEntity(clonedEntityID);

		// Clone the components from the source entity to the cloned entity
		auto sourceComponents = sourceEntity->GetComponents();
		for (const auto& pair : sourceComponents) {
			Component* sourceComponent = pair.second;
			// You may need to implement a copy constructor or clone method for your components
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes

			// Add the cloned component to the cloned entity
			clonedEntity->AddComponent(std::unique_ptr<Component>(clonedComponent));
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
	}
}

