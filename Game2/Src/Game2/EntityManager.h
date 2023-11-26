#pragma once
/******************************************************************************/
/*!
\file		EntityManager.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Entity Manager

 */
 /******************************************************************************/
#include "Entity.h"
#include "Prefab.h"

namespace Engine
{
	class EntityManager
	{
	public:
		EntityManager() {};
		~EntityManager() {};

		EntityID CreateEntity();
		EntityID CreateEntityFromPrefab(const Prefab& prefab);
		Entity* GetEntity(EntityID id);
		std::unordered_map<EntityID, std::unique_ptr<Entity>>* GetEntities();
		EntityID CloneEntity(EntityID sourceEntityID);
		//std::vector<EntityID> CloneEntity(EntityID sourceEntityID, int num) possible overload specify number of clones
		void DestroyEntity(EntityID entity);

		std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
		static EntityID nextEntityID;


	private:
		
	};

}