#pragma once
/******************************************************************************/
/*!
\file		Prefab.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Entity Manager

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

    void AddNewComponent(ComponentType type);

	std::unordered_map<ComponentType, Component*> GetComponents() const;

	std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
	};
}