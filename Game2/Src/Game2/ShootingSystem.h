#pragma once
/******************************************************************************/
/*!
\file		ShootingSystem.h
\author		Tay Jun Feng Vance
\par		junfengvance.t@digipen.edu
\date		22/01/2024
\brief		Contains the declarations for shooting system class.

 */
 /******************************************************************************/
#include "ShootingComponent.h"
#include "Vector2d.h"
#include "pch.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "PathfindingSystem.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "input.h"
#include "PrefabManager.h"
#include "EngineTypes.h"
#include "AssetManager.h"
#include <vector>
#include "System.h"

namespace Engine
{
	class ShootingSystem : public System
	{
		//void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

		//bool CanShoot(ShootingComponent* shootingComponent);

		//void Shoot(ShootingComponent* shootingComponent);

        void Initialize();
        ShootingSystem(); // Constructor to initialize shooting rate variables
        ShootingSystem(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm) : entityManager(em), prefabManager(pm) {}
        void Update(float deltaTime, bool shootingCheck);
        //void ShootArrow(const VECTORMATH::Vec2& archerPosition, const VECTORMATH::Vec2& targetPosition);

    private:
        // Shooting properties
        //float shootingSpeed; // Speed of arrows when shot
        //float shootingRate;  // Time between consecutive shots
        //float shootCooldown; // Timer to track time until the next shot is allowed

        // Arrow pool properties
        //static const int maxPoolSize = 100; // Maximum pool size
        //std::vector<Arrow> arrows;           // Container to store active arrows

        //void UpdateArrows();
        //void HandleCollisions(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);
        //void AddArrowToPool(const VECTORMATH::Vec2& position, const VECTORMATH::Vec2& velocity, float damage);

        //void CheckEntitiesForShooting(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, CollisionSystem& collisionSystem);
        //void ShootArrow(EntityID shooterID, EntityID targetID, std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

        std::shared_ptr<Engine::EntityManager> entityManager;
        Engine::PrefabManager* prefabManager;
        Entity* targetEntity = nullptr;
        CollisionSystem collisionSystem;  // Declare an instance of CollisionSystem
        TextureComponent* textureCheck;

        float spawnTimer;
        float spawnInterval;
    };
}