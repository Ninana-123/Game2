/******************************************************************************/
/*!
\file		ScriptComponent.cpp
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Definition of the ScriptComponent class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "pch.h"
#include "ScriptFactory.h"
#include "ScriptComponent.h"

namespace Engine
{
	void ScriptComponent::InitializeScript()
	{
		script = g_ScriptFactory->AddScript(currentScriptType, entity);
		std::cout << "Script Type: " << static_cast<int>(currentScriptType) << std::endl;
		std::cout << "Script EntityID: " << static_cast<int>(entity) << std::endl;
	}

	void ScriptComponent::SetScriptType(ScriptType type)
	{

		if (currentScriptType != type)
		{
			currentScriptType = type;
			// Now you can create a new script object based on the type
			script = g_ScriptFactory->AddScript(type, entity);
			std::cout << "New Script Type: " << static_cast<int>(currentScriptType) << std::endl;
		}
	}

	void ScriptComponent::SetEntity(EntityID entity_)
	{ 
		entity = entity_; 
	}

	std::string ScriptComponent::ScriptToString(ScriptType type)
	{
		std::string buffer;
		switch (type)
		{
		case ScriptType::Empty:
		{
			return buffer = "Empty";
		}
		case ScriptType::infantry:
		{
			return buffer = "Infantry";
		}
		case ScriptType::tower:
		{
			return buffer = "Tower";
		}
		default:
			buffer = "Unknown";
			break;
		}
		return buffer;
	}

	Script* ScriptComponent::GetScript() const
	{
		return script;
	}

	ComponentType  ScriptComponent::GetType() const
	{ 
		return ComponentType::Script; 
	}

	Component* ScriptComponent::Clone() const
	{
		ScriptComponent* cloneComponent = new ScriptComponent();
		cloneComponent->currentScriptType = currentScriptType;
		//cloneComponent->statsInitialized = statsInitialized;
		return cloneComponent;
	}

	void  ScriptComponent::Serialize(std::ostream& outputStream) const
	{
		outputStream << "ID: " << static_cast<int>(entity) << '\n';
		outputStream << "type: " << static_cast<int>(currentScriptType) << '\n';
	}

	void  ScriptComponent::Deserialize(std::istream& inputStream)
	{
		std::string temp;
		int ID;
		int script_index;
		inputStream >> temp >> ID;
		inputStream >> temp >> script_index;
		entity = static_cast<EntityID>(ID);
		currentScriptType = static_cast<ScriptType>(script_index);
	}
}