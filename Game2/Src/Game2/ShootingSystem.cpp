#include "pch.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ShootingSystem.h"
#include "Application.h"

bool entityCreated = false;

namespace Engine
{
    //void ShootingSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) {
    //    for (const auto& it : *entities) {
    //        Entity* entity = it.second.get();

    //        if (entity->HasComponent(ComponentType::Shooting)) {
    //               ShootingComponent* shootingcomponent = dynamic_cast<ShootingComponent*>(entity->GetComponent(ComponentType::Shooting));

    //            if (CanShoot(shootingcomponent)) {
    //                Shoot(shootingcomponent);
    //            }
    //        }
    //    }
    //}

    //bool ShootingSystem::CanShoot(ShootingComponent* shootingComponent) {
    //    // Add your conditions here for when the entity can shoot
    //    // For example, you might check cooldown time, ammunition count, etc.
    //    // For simplicity, we'll always return true here.
    //    return true;
    //}

    //void ShootingSystem::Shoot(ShootingComponent* shootingComponent) {
    //    // Perform shooting action here
    //    // For now, we'll just print a message
    //    std::cout << "Shooting!" << std::endl;
    //}

    void ShootingSystem::Initialize() {

    }

    ShootingSystem::ShootingSystem() : entityManager(), prefabManager(), collisionSystem()
    {
    }

    void ShootingSystem::Update(float deltaTime, bool shootingCheck) {
        while (!collisionSystem->CollisionQueue.empty())
        {
            CollisionVector.push_back(collisionSystem->CollisionQueue.front());
            collisionSystem->CollisionQueue.pop();
        }
        while (!collisionSystem->PlayerArrowQueue.empty())
        {
            PlayerArrowVector.push_back(collisionSystem->PlayerArrowQueue.front());
            collisionSystem->PlayerArrowQueue.pop();
        }
        if (!PlayerArrowVector.empty())
        {
            Entity* Player = entityManager.get()->GetEntity(PlayerArrowVector.front().second);
            Entity* Arrow = entityManager.get()->GetEntity(PlayerArrowVector.front().first); // Could be second?? didnt check
            Player->AddNewComponent(ComponentType::Stats);
            StatsComponent* PlayerStats = dynamic_cast<StatsComponent*>(Player->GetComponent(ComponentType::Stats));
            PlayerStats->health -= 1;
            entityManager.get()->DestroyEntity(Arrow->GetID());
            PlayerArrowVector.erase(PlayerArrowVector.begin());
        }
        if (shootingCheck && !entityCreated) 
        {
            Prefab* arrowPrefab = prefabManager->GetPrefab(10);
            EntityID arrowID = entityManager->CreateEntityFromPrefab(*arrowPrefab);
            entityCreated = true;
            Arrow arrow;
            arrow.active = true;
            arrow.entity = arrowPrefab;
            
            arrows.push_back(arrow);
            //TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(arrow.entity->GetComponent(ComponentType::Transform));
            if (!CollisionVector.empty())
            {
                Entity* Tower = entityManager.get()->GetEntity(CollisionVector.front().first); // Could be second?? didnt check
                Entity* Player = entityManager.get()->GetEntity(CollisionVector.front().second); // Could be second?? didnt check
                Entity* Arrow = entityManager.get()->GetEntity(arrowID); // Could be second?? didnt check
                Arrow->AddNewComponent(ComponentType::Physics);
                Arrow->AddNewComponent(ComponentType::Collision);
                TransformComponent* TowerTransform = dynamic_cast<TransformComponent*>(Tower->GetComponent(ComponentType::Transform));
                TransformComponent* PlayerTransform = dynamic_cast<TransformComponent*>(Player->GetComponent(ComponentType::Transform));
                TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(Arrow->GetComponent(ComponentType::Transform));
                TextureComponent* ArrowTexture = dynamic_cast<TextureComponent*>(Arrow->GetComponent(ComponentType::Texture));
                ArrowTexture->textureKey = { 42, 0 };
                CollisionComponent* ArrowCollision = dynamic_cast<CollisionComponent*>(Arrow->GetComponent(ComponentType::Collision));
                ArrowCollision->layer = Layer::World;
                PhysicsComponent* ArrowPhysics = dynamic_cast<PhysicsComponent*>(Arrow->GetComponent(ComponentType::Physics));
                VECTORMATH::Vec2 Vel = PlayerTransform->position - TowerTransform->position;
                /*VECTORMATH::Vector2DNormalize(Vel, Vel);*/
                ArrowTransform->rot = atan2(Vel.y, Vel.x);
                ArrowPhysics->velocity = Vel;
                ArrowPhysics->mass = 0.001f;
                ArrowTransform->position = TowerTransform->position;
                //CollisionVector.erase(CollisionVector.begin());
                CollisionVector.pop_back();
            }
        }
        if (entityCreated)
        {
            spawnTimer -= deltaTime;
            if (spawnTimer < 0)
            {
                entityCreated = false;
                spawnTimer = spawnInterval;
            }
        }
       /* for (const auto& temp : arrows)
        {
            BehaviourComponent
            temp.entity.
        }*/
        /*if (entitycreated) {
            spawnTimer += deltaTime;
            if (spawnTimer >= spawnInterval) {
                entitycreated = false;
            }
        }*/
    }



}