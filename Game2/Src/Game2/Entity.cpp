#include "pch.h"
#include "Entity.h"
#include "Component.h"

namespace Engine 
{
	void Entity::AddComponent(std::unique_ptr<Component> component)
	{
		components.emplace(component->GetType(), std::move(component));
	}

	void Entity::AddNewComponent(ComponentType type)
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

	Component* Entity::GetComponent(ComponentType type) const
	{
		auto it = components.find(type);

		if (it != components.end())
		{
			return it->second.get();
		}
		else return nullptr;
	}

	std::unordered_map<ComponentType, Component*> Entity::GetComponents() const
	{
		std::unordered_map<ComponentType, Component*> result;
		for (const auto& pair : components) {
			result[pair.first] = pair.second.get(); // Store raw pointers
		}
		return result;
	}

	bool Entity::HasComponent(ComponentType type) const 
	{
		return components.find(type) != components.end();
	}

}



