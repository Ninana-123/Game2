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
#include "Tower.h"
#include "Archer.h"

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
		case ScriptType::archer:
		{
			return buffer = "Archer";
		}
		default:
			buffer = "Unknown";
			break;
		}
		return buffer;
	}

	Script* ScriptComponent::GetScript() const
	{
		switch (currentScriptType)
		{
			case ScriptType::Empty:
			{
				return script;
			}
			case ScriptType::infantry:
			{
				return script;
			}
			case ScriptType::tower:
			{
				Tower* tower = dynamic_cast<Tower*>(script);
				return tower;
			}
			case ScriptType::archer:
			{
				Archer* archer = dynamic_cast<Archer*>(script);
				return archer;
			}
			default:
			{
				return script;
			}
		}
	}

	ComponentType ScriptComponent::GetType() const
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
		outputStream << "Running: " << static_cast<int>(run) << '\n';
	}

	void  ScriptComponent::Deserialize(std::istream& inputStream)
	{
		std::string temp;
		int ID;
		int script_index;
		int running;
		inputStream >> temp >> ID;
		inputStream >> temp >> script_index;
		inputStream >> temp >> running;
		entity = static_cast<EntityID>(ID);
		currentScriptType = static_cast<ScriptType>(script_index);
		run = static_cast<bool>(running);
	}
}