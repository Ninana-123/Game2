/******************************************************************************/
/*!
\file		ComponentFactory.h
\author 	Tristan Tham Rui Hong 
\par    	email: t.tham@digipen.edu
\date   	29/09/2923
\brief		Declaration of the ComponentFactory class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once
#include "pch.h"
#include "Component.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "TextureComponent.h"
#include "PhysicsComponent.h"

namespace Engine
{

	class ComponentFactory
	{
	public:

		using CreationFunction = std::function<std::unique_ptr<Component>()>;

		ComponentFactory();

		static void RegisterComponent(ComponentType type, CreationFunction function);

		static std::unique_ptr<Component> CreateComponent(ComponentType type);

		static ComponentType StringToComponentType(const std::string& typeString);
		static std::string ComponentTypeToString(ComponentType type);

	private:
		static std::unordered_map<ComponentType, CreationFunction>& componentRegistry();
	};

}