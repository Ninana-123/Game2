/******************************************************************************/
/*!
\file		EntityManager.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Entity Manager

 */
 /******************************************************************************/

#ifndef ENGINE_ENTITYMANAGER_H
#define ENGINE_ENTITYMANAGER_H

#include "Entity.h"
#include "Prefab.h"

namespace Engine
{
	class EntityManager
	{
	public:
		/*!
		\brief
		Constructor for the EntityManager class.
		*/
		EntityManager() {};

		/*!
		\brief
		Destructor for the EntityManager class.
		*/
		~EntityManager() {};

		/*!
		\brief
		Creates a new entity and returns its unique identifier.

		\return
		The unique identifier (EntityID) of the newly created entity.
		*/
		EntityID CreateEntity();

		/*!
		\brief
		Creates a new entity based on a prefab and returns its unique identifier.

		\param prefab
		The prefab to use as a template for the new entity.

		\return
		The unique identifier (EntityID) of the newly created entity.
		*/
		EntityID CreateEntityFromPrefab(const Prefab& prefab);

		/*!
		\brief
		Returns a pointer to the entity with the specified unique identifier.

		\param id
		The unique identifier (EntityID) of the entity to retrieve.

		\return
		A pointer to the entity if found, nullptr otherwise.
		*/
		Entity* GetEntity(EntityID id);

		/*!
		\brief
		Returns a pointer to the unordered map containing all entities.

		\return
		A pointer to the unordered map of entities.
		*/
		std::unordered_map<EntityID, std::unique_ptr<Entity>>* GetEntities();

		/*!
		\brief
		Clones an existing entity and returns the unique identifier of the new entity.

		\param sourceEntityID
		The unique identifier (EntityID) of the entity to clone.

		\return
		The unique identifier (EntityID) of the newly created clone.
		*/
		EntityID CloneEntity(EntityID sourceEntityID);

		EntityID CloneEntity(Entity* sourceEntity);

		/*!
		\brief
		Destroys the entity with the specified unique identifier.

		\param entity
		The unique identifier (EntityID) of the entity to destroy.
		*/
		void DestroyEntity(EntityID entity);

		/*!
		\brief
		Unordered map containing all entities, mapped by their unique identifiers.
		*/
		std::unordered_map<EntityID, std::unique_ptr<Entity>> entities;

		/*!
		\brief
		Static variable representing the next available unique identifier for entities.
		*/
		static EntityID nextEntityID;

		// Method to get iterators to the beginning and end of the entities collection
		auto begin() { return entities.begin(); }
		auto end() { return entities.end(); }

		void AddToStorage(EntityID entityID);
		void RemoveFromStorage(EntityID entityID);
		void DestroyEntitiesInStorage();

	protected:
		std::vector<EntityID> storage;
	};

}
#endif ENGINE_ENTITYMANAGER_H