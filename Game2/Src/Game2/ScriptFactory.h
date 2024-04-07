/******************************************************************************/
/*!
\file		ScriptFactory.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	20/3/2024
\brief		Declaration of the ScriptFactory class. ScriptFactory helps with instantiating
            Script objects and removing them

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#ifndef ENGINE_SCRIPTFACTORY_H
#define ENGINE_SCRIPTFACTORY_H

#include "pch.h"
#include "EngineTypes.h"
#include "ScriptSystem.h"

namespace Engine
{
    class ScriptSystem;
    class ScriptFactory
    {
    public:
        using CreationFunction = std::function<std::unique_ptr<Script>(Entity*)>;

        ScriptFactory(ScriptSystem* scriptSystem);

        // Function to create script
        void CreateScript(ScriptType type, CreationFunction function);

        Script* AddScript(ScriptType type, EntityID entityId);

        ScriptSystem* GetScriptSystem();

        //void RemoveScript(EntityID entityId);

    private:
        ScriptSystem* SS;
        std::unordered_map<ScriptType, CreationFunction>& scriptRegistry();
    };
}
#endif ENGINE_SCRIPTFACTORY_H