#pragma once
/******************************************************************************/
/*!
\file		Prefab.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Prefab class

 */
 /******************************************************************************/

#include "pch.h"
#include "Component.h"
#include "ComponentFactory.h"

namespace Engine
{
	class Prefab
	{
	public:
		Prefab(PrefabID id) : id(id), name("\0") {};
		~Prefab() { components.clear(); }

		void AddComponent(std::unique_ptr<Component> component);
		void AddNewComponent(ComponentType type);
		Component* GetComponent(ComponentType type) const;
		bool HasComponent(ComponentType type) const;
	
		PrefabID GetID() const { return id; }
		std::string GetName() const { return name; }

		std::unordered_map<ComponentType, Component*> GetComponents() const;

		std::unordered_map<ComponentType, std::unique_ptr<Component>> components;

		PrefabID id;
		std::string name;
	};
}