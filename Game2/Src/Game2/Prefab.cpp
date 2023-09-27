#include "pch.h"
#include "Prefab.h"

namespace Engine
{
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

