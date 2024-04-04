/******************************************************************************/
/*!
\file		ScriptComponent.cpp
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptComponent class

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

	void ScriptComponent::SetScriptType(ScriptType type)
	{
		if (currentScriptType != type)
		{
			currentScriptType = type;
			// Now you can create a new script object based on the type
			script = g_ScriptFactory.AddScript(type, entity);
		}
	}

	void ScriptComponent::SetEntity(Entity * entity_)
	{ 
		this->entity = entity_; 
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
		//cloneComponent->statsInitialized = statsInitialized;
		return cloneComponent;
	}

	void  ScriptComponent::Serialize(std::ostream& outputStream) const
	{
		UNREFERENCED_PARAMETER(outputStream);
	}

	void  ScriptComponent::Deserialize(std::istream& inputStream)
	{
		UNREFERENCED_PARAMETER(inputStream);
	}
}