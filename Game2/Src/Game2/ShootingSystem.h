/******************************************************************************/
/*!
\file		ShootingSystem.h
\author		Tay Jun Feng Vance
\par		junfengvance.t@digipen.edu
\date		22/01/2024
\brief		Contains the declarations for shooting system class.

 */
 /******************************************************************************/
#pragma once
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "input.h"
#include "PrefabManager.h"
#include "EngineTypes.h"
#include "AssetManager.h"
#include "SystemsManager.h"


namespace Engine
{
	class ShootingSystem
	{
    public:
		//void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

		//bool CanShoot(ShootingComponent* shootingComponent);

		//void Shoot(ShootingComponent* shootingComponent);

        ShootingSystem(); // Constructor to initialize shooting rate variables

        ShootingSystem(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm, Engine::CollisionSystem* cs)
            : entityManager(em), prefabManager(pm), collisionSystem(cs) {}

        /**************************************************************************/
        /*!
        \brief Sets the target entity for the in-game GUI.

        \param[in] entity
        Pointer to the target entity.
        */
        /**************************************************************************/
        inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }

        /**************************************************************************/
        /*!
        \brief Gets the target entity for the in-game GUI.

        \return
        Pointer to the target entity.
        */
        /**************************************************************************/
        inline Entity* TargetEntityGetter() { return targetEntity; }

        void Initialize();

        void Update(float deltaTime, bool shootingCheck, std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, AssetManager& assetManaager, AudioEngine& audioEngine);
        std::vector<std::pair<EntityID, EntityID>> CollisionVector;

        //void ShootArrow(const VECTORMATH::Vec2& archerPosition, const VECTORMATH::Vec2& targetPosition);

    private:
        // Shooting properties
        //float shootingSpeed; // Speed of arrows when shot
        //float shootingRate;  // Time between consecutive shots
        //float shootCooldown; // Timer to track time until the next shot is allowed
        struct Arrow
        {
            Prefab* entity;
            bool active;
        };
        // Arrow pool properties
        //static const int maxPoolSize = 100; // Maximum pool size
        std::vector<Arrow> arrows;           // Container to store active arrows

        //void UpdateArrows();
        //void HandleCollisions(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);
        //void AddArrowToPool(const VECTORMATH::Vec2& position, const VECTORMATH::Vec2& velocity, float damage);

        //void CheckEntitiesForShooting(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, CollisionSystem& collisionSystem);
        //void ShootArrow(EntityID shooterID, EntityID targetID, std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

        std::shared_ptr<Engine::EntityManager> entityManager;
        Engine::CollisionSystem* collisionSystem;  // Declare an instance of CollisionSystem
        Engine::PrefabManager* prefabManager;
        Entity* targetEntity = nullptr;
        // TextureComponent* textureCheck;
        float spawnInterval = 2.0;
        float spawnTimer = spawnInterval;
    };
}