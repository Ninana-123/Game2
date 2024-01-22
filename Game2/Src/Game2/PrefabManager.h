/******************************************************************************/
/*!
\file		PrefabManager.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Prefab Manager

 */
 /******************************************************************************/
#ifndef ENGINE_PREFABMANAGER_H
#define ENGINE_PREFABMANAGER_H

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
		Prefab* GetPrefab(std::string name);
		std::unordered_map<PrefabID, std::unique_ptr<Prefab>>* GetPrefabs();
		PrefabID ClonePrefab(PrefabID sourcePrefabID);
		void DestroyPrefab(PrefabID prefab);

		std::unordered_map<PrefabID, std::unique_ptr<Prefab>> prefabs;
		static PrefabID nextPrefabID;
	private:

	};

}
#endif ENGINE_PREFABMANAGER_H