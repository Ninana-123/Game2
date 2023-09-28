#pragma once
#include "pch.h"
#include "Component.h"
#include "ComponentFactory.h"

namespace Engine
{
	class Prefab
	{
	public:

    void AddNewComponent(ComponentType type);

	std::unordered_map<ComponentType, Component*> GetComponents() const;

	std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
	};
}