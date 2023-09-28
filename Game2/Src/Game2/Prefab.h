#pragma once
#include "pch.h"
#include "Component.h"

namespace Engine
{
	class Prefab
	{
	public:
	std::unordered_map<ComponentType, Component*> GetComponents() const;

	std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
	};
}