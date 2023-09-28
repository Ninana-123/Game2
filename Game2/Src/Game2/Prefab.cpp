#include "pch.h"
#include "Prefab.h"

namespace Engine
{
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
			std::cout << "Failed to add new component." << std::endl;
		}
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
}

