/******************************************************************************/
/*!
\file		ScriptSystem.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptSystem class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "pch.h"
#include "Entity.h"
#include "ScriptComponent.h"
#include "EntityManager.h"

namespace Engine
{
	class ScriptSystem
	{
	public:
		
		/*!
		\brief
		Default constructor 

		\param entityManager
		input EM object to link entitymanager
		*/
		ScriptSystem(EntityManager& entityManager) : entityManager(entityManager) {} //access to EM

		/*!
		\brief
		Initialize function to load deserialized scripts
		*/
		//void Initialize(); for possible deserialized scripts

		/*!
		\brief
		Creates and adds a new script object and maps it to the entity

		\param entityID
		entityID of script parent

		*/
		template<typename T>
		void AddScript(EntityID entityId) 
		{
			auto it = scripts.find(entityId);
			if (it != scripts.end()) 
			{
				scripts.erase(it); //scrap and renew existing script
			}

			// Create a new script and assign it to the entity
			scripts[entityId] = std::make_unique<T>();
		}

		/*!
		\brief
		Removes a script object from an entity

		\param entityId
		ID of target entity to remove script object from

		*/
		void RemoveScript(EntityID entityId)
		{
			scripts.erase(entityId);
		}

		/*!
		\brief
		Update function that updates all existing scripts
		*/
		void UpdateScripts() 
		{
			for (auto& pair : scripts)
			{
				pair.second->Update(); 
			}
		}

	private:
		EntityManager& entityManager; //EM instance
		std::unordered_map<EntityID, std::unique_ptr<Script>> scripts; //pointers to all existing scripts
	};
}