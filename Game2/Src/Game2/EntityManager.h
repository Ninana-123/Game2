#pragma once
#include "Entity.h"

namespace Engine
{
	class EntityManager
	{
	public:
		EntityManager() {};
		~EntityManager();

		EntityID CreateEntity();
		EntityID CreateEntityFromPrefab();
		Entity* GetEntity(EntityID id);
		//const std::unordered_map<EntityID, std::unique_ptr<Entity>>& GetEntities() const;
		EntityID CloneEntity(EntityID sourceEntityID);
		//std::vector<EntityID> CloneEntity(EntityID sourceEntityID, int num) possible overload specify number of clones
		void DestroyEntity(EntityID entity);

		void UpdateEntities();

		std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
		static EntityID nextEntityID;
	private:
		
	};

}