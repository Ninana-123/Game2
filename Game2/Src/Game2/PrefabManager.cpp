/******************************************************************************/
/*!
\file		PrefabManager.cpp
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the definitions of the Prefab Manager

 */
 /******************************************************************************/
#include "pch.h"
#include "PrefabManager.h"

namespace Engine
{
	PrefabID PrefabManager::nextPrefabID = 0;

	PrefabID PrefabManager::CreatePrefab()
	{
		PrefabID prefabID = nextPrefabID++;
		prefabs.emplace(prefabID, std::make_unique<Prefab>(prefabID));
		return prefabID;
	}

	Prefab* PrefabManager::GetPrefab(PrefabID id)
	{
		auto it = prefabs.find(id);
		return (it != prefabs.end()) ? it->second.get() : nullptr;
	}

	Prefab* PrefabManager::GetPrefab(std::string name)
	{
		for (auto& pair : prefabs)
		{
			if (pair.second->GetName() == name)
			{
				return pair.second.get();
			}
		}
		return nullptr;
	}

	std::unordered_map<PrefabID, std::unique_ptr<Prefab>>* PrefabManager::GetPrefabs()
	{
		return &prefabs;
	}

	PrefabID PrefabManager::ClonePrefab(PrefabID sourcePrefabID) 
	{
		// Get the source entity to clone
		Prefab* sourcePrefab = GetPrefab(sourcePrefabID);
		if (!sourcePrefab)
		{
			// Entity not found
			return UINT_MAX;
		}

		// Create a new entity as a clone
		PrefabID clonedPrefabID = CreatePrefab();
		Prefab* clonedPrefab = GetPrefab(clonedPrefabID);

		// Clone the components from the source entity to the cloned entity
		auto sourceComponents = sourcePrefab->GetComponents();
		for (const auto& pair : sourceComponents) {
			Component* sourceComponent = pair.second;
			// You may need to implement a copy constructor or clone method for your components
			Component* clonedComponent = sourceComponent->Clone(); // Implement Clone() in your component classes

			// Add the cloned component to the cloned entity
			clonedPrefab->AddComponent(std::unique_ptr<Component>(clonedComponent));
		}

		return clonedPrefabID;
	}
	
	void PrefabManager::DestroyPrefab(PrefabID prefab)
	{
		auto it = prefabs.find(prefab);
		if (it != prefabs.end())
		{
			prefabs.erase(it);

			// create a buffer to hold new entities
			std::unordered_map<PrefabID, std::unique_ptr<Prefab>> updatedPrefabs;

			// reassign IDs and populate the new map
			PrefabID newID = 0;
			for (auto& pair : prefabs)
			{
				if (pair.first != prefab)
				{
					pair.second->id = newID;
					updatedPrefabs[newID] = std::move(pair.second);
					++newID;
				}
			}

			// update original map with buffer map
			prefabs = std::move(updatedPrefabs);
		}
	}
}