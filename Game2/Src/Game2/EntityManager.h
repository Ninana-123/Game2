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
		Entity* GetEntity(EntityID id);
		EntityID CloneEntity(EntityID sourceEntityID);
		//std::vector<EntityID> CloneEntity(EntityID sourceEntityID, int num) possible overload specify number of clones
		void DestroyEntity(EntityID entity);

		void Update();

	private:
		static EntityID nextEntityID;
		std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
		
	};

}