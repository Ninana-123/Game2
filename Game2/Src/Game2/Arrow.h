#pragma once

#ifndef ARROW_H_
#define ARROW_H_

#include "Vector2d.h"
#include "pch.h"
#include "System.h"
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


namespace Engine
{
    struct Arrow
    {
        VECTORMATH::Vec2 position;
        VECTORMATH::Vec2 velocity;
        bool isActive; // Flag to determine if the arrow is active or not
        float damage;  // Damage value for the arrow (adjust as needed)
    };

    class ShootingSystem
    {
    public:

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

#endif