/******************************************************************************/
/*!
\file		TempStateMachine.h
\author 	Tristan Tham Rui Hong

\email		t.tham@digipen.edu

\date   	30/01/2024
\brief		This file contains the declaraton of the states behaviours
			that the entities will be using.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include <iostream>
#include <string>
#include <memory>
#include "Entity.h"
#include "Component.h"
#include "AssetManager.h"

extern bool isGameOver;

namespace Engine
{
	class StateMachine
	{
	public:

		/**************************************************************************/
		/*!
		\brief Updates the entities in the game.

		\param entities
			A pointer to the unordered map containing the entities.

		\param audioEngine
			Reference to the AudioEngine object.

		\param assetManager
			Reference to the AssetManager object.
		*/
		/**************************************************************************/
		void UpdateEntities(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, AudioEngine& audioEngine, AssetManager& assetManager);

		/**************************************************************************/
		/*!
		\brief Performs idle behavior for the entity.

		\param entity
			A pointer to the entity to perform idle behavior.
		*/
		/**************************************************************************/
		void Idle(Entity* entity);

		/**************************************************************************/
		/*!
		\brief Performs walking behavior for the entity.

		\param entity
			A pointer to the entity to perform walking behavior.

		\param audioEngine
			Reference to the AudioEngine object.

		\param assetManager
			Reference to the AssetManager object.
		*/
		/**************************************************************************/
		void Walking(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager);

		/**************************************************************************/
		/*!
		\brief Performs attack behavior for the entity.

		\param entity
			A pointer to the entity to perform attack behavior.

		\param audioEngine
			Reference to the AudioEngine object.

		\param assetManager
			Reference to the AssetManager object.
		*/
		/**************************************************************************/
		void Attack(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager);

		/**************************************************************************/
		/*!
		\brief Handles the death of the entity.

		\param entity
			A pointer to the entity that has died.
		*/
		/**************************************************************************/
		void Death(Entity* entity, AudioEngine& audioEngine, AssetManager& assetManager);
	};
	
}
