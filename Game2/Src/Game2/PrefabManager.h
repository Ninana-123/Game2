#pragma once
/******************************************************************************/
/*!
\file		PrefabManager.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Prefab Manager

 */
 /******************************************************************************/

#include "Prefab.h"

namespace Engine
{
	class PrefabManager
	{
	public:
		PrefabManager() {};
		~PrefabManager() {};

		PrefabID CreatePrefab();
		Prefab* GetPrefab(PrefabID id);
		void DestroyPrefab(PrefabID prefab);
		/*
		std::unordered_map<EntityID, std::unique_ptr<Entity>>* GetEntities();
		EntityID CloneEntity(EntityID sourceEntityID);
		*/

		std::unordered_map<PrefabID, std::unique_ptr<Prefab>> prefabs;
		static PrefabID nextPrefabID;
	private:

	};

}