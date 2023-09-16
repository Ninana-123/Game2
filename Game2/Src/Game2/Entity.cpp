#include "pch.h"
#include "Entity.h"

namespace Engine 
{
	void Engine::Entity::AddComponent(std::unique_ptr<Component> component)
	{
		components.emplace(component->GetType(), std::move(component));
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

	void Entity::Update()
	{
		
	}


}



