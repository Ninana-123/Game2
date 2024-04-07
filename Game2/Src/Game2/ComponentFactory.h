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
#ifndef ENGINE_COMPONENTFACTORY_H
#define ENGINE_COMPONENTFACTORY_H

#include "pch.h"
#include "Component.h"
#include "CollisionComponent.h"
#include "TransformComponent.h"
#include "TextureComponent.h"
#include "PhysicsComponent.h"
#include "RenderDataComponent.h"
#include "SpriteComponent.h"
#include "PathfindingComponent.h"
#include "BehaviourComponent.h"
#include "StatsComponent.h"
#include "ShootingComponent.h"
#include "ScriptComponent.h"

namespace Engine
{
	class ComponentFactory
	{
	public:

		using CreationFunction = std::function<std::unique_ptr<Component>()>;

		/*!**********************************************************************
		\brief
		Constructor for the ComponentFactory class.
		*************************************************************************/
		ComponentFactory();

		/*!**********************************************************************
		\brief
		Registers a component creation function for a given ComponentType.
		\param type
		The ComponentType to associate with the creation function.
		\param function
		The creation function to register for the specified ComponentType.
		*************************************************************************/
		static void RegisterComponent(ComponentType type, CreationFunction function);

		/*!**********************************************************************
		\brief
		Creates a unique_ptr to a Component based on the specified ComponentType.
		\param type
		The ComponentType for which to create a Component.
		\return
		A unique_ptr to the created Component or nullptr if the ComponentType is unknown.
		*************************************************************************/
		static std::unique_ptr<Component> CreateComponent(ComponentType type);

		/*!**********************************************************************
		\brief
		Converts a string representation of a ComponentType to the corresponding enum value.
		\param typeString
		The string representation of the ComponentType.
		\return
		The ComponentType enum value corresponding to the provided string.
		*************************************************************************/
		static ComponentType StringToComponentType(const std::string& typeString);

		/*!**********************************************************************
		\brief
		Converts a ComponentType enum value to its string representation.
		\param type
		The ComponentType enum value.
		\return
		The string representation of the provided ComponentType.
		*************************************************************************/
		static std::string ComponentTypeToString(ComponentType type);

	private:

		/*!**********************************************************************
		\brief
		Returns a reference to the component registry, a mapping of ComponentType to CreationFunction.
		\return
		A reference to the component registry, where ComponentType is mapped to CreationFunction.
		*************************************************************************/
		static std::unordered_map<ComponentType, CreationFunction>& componentRegistry();
	};
}
#endif ENGINE_COMPONENTFACTORY_H