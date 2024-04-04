#pragma once

#include "pch.h"
#include "ScriptFactory.h"
#include "Tower.h"


namespace Engine
{
    ScriptFactory::ScriptFactory(ScriptSystem& scriptSystem) : SS(scriptSystem)
    {
        // Register script types with their creation functions
        CreateScript(ScriptType::tower, [](Entity* entity) { return std::make_unique<Tower>(); });
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

    std::unique_ptr<Script> ScriptFactory::AddScript(ScriptType type, Entity* entity)
    {
        // Check if the script type is registered
        auto it = scriptRegistry().find(type);
        if (it != scriptRegistry().end())
        {
            auto script = it->second(entity);
            SS.RegisterScript(entity->GetID(), std::move(script));// Register the script in the system
            return script;
        }
        else
        {
            return nullptr; //No script for the type
        }
    }

    //void RemoveScript(EntityID entityId)
    //{

    //}

}
