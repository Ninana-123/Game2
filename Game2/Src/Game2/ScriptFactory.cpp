/******************************************************************************/
/*!
\file		ScriptFactory.cpp
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	07/03/2923
\brief		Definitions of the ScriptFactory class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once

#include "pch.h"
#include "ScriptFactory.h"
#include "Tower.h"


namespace Engine
{
    ScriptFactory::ScriptFactory(ScriptSystem& scriptSystem) : SS(scriptSystem)
    {
        // Register script types with their creation functions
        CreateScript(ScriptType::tower, [](Entity* entity) { return std::make_unique<Tower>(entity); });
    }

    std::unordered_map<ScriptType, ScriptFactory::CreationFunction>& ScriptFactory::scriptRegistry()
    {
        static std::unordered_map<ScriptType, CreationFunction> registry;
        return registry;
    }

    void ScriptFactory::CreateScript(ScriptType type, CreationFunction function)
    {
        scriptRegistry()[type] = function;
    }

    Script* ScriptFactory::AddScript(ScriptType type, EntityID entity)
    {
        // Check if the script type is registered
        auto it = scriptRegistry().find(type);
        if (it != scriptRegistry().end())
        {
            auto script = it->second( SS.QueryEntityPtr(entity) ); //use EM from SS
            SS.RegisterScript(entity, std::move(script)); // Register the script in the system
            // Return a pointer to the script object
            return SS.GetScript(entity); // Assuming GetScript returns a pointer to the registered script
        }
        else
        {
            return nullptr; // No script for the type
        }
    }

    //void RemoveScript(EntityID entityId)
    //{

    //}

}
