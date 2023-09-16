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
		void DestroyEntity(EntityID entity);

		void Update();

	private:
		static EntityID nextEntityID;
		std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;
		
	};

}