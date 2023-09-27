#pragma once
#include "Entity.h"
#include "Prefab.h"

namespace Engine
{
	class EntityManager
	{
	public:
		EntityManager() {};
		~EntityManager();

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