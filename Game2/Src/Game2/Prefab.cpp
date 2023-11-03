/******************************************************************************/
/*!
\file		Prefab.cpp
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the definitions of the Prefab Class

 */
 /******************************************************************************/

#include "pch.h"
#include "Prefab.h"

namespace Engine
{
	void Prefab::AddComponent(std::unique_ptr<Component> component)
	{
		components.emplace(component->GetType(), std::move(component));
	}

	void Prefab::AddNewComponent(ComponentType type)
	{
		auto newComponent = ComponentFactory::CreateComponent(type);

		if (newComponent)
		{
			// Emplace the new component into the entity's container
			components.emplace(type, std::move(newComponent));
		}
		else
		{
			//std::cout << "Failed to add new component." << std::endl;
		}
	}

	Component* Prefab::GetComponent(ComponentType type) const
	{
		auto it = components.find(type);

		if (it != components.end())
		{
			return it->second.get();
		}
		else return nullptr;
	}

	std::unordered_map<ComponentType, Component*> Prefab::GetComponents() const
	{
		std::unordered_map<ComponentType, Component*> result;
		for (const auto& pair : components)
		{
			result[pair.first] = pair.second.get(); // Store raw pointers
		}

		return result;
	}

	bool Prefab::HasComponent(ComponentType type) const
	{
		return components.find(type) != components.end();
	}
	
}

