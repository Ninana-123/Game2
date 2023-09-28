#pragma once
#include "pch.h"
#include "Component.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"

namespace Engine
{

	class ComponentFactory
	{
	public:

		using CreationFunction = std::function<std::unique_ptr<Component>()>;

		ComponentFactory();

		static void RegisterComponent(ComponentType type, CreationFunction function);

		static std::unique_ptr<Component> CreateComponent(ComponentType type);

	private:
		static std::unordered_map<ComponentType, CreationFunction>& componentRegistry();
	};

}