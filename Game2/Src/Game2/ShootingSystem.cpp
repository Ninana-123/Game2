/******************************************************************************/
/*!
\file		ShootingSystem.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius@digipen.edu, 2201807
\co		    Teo Sheen Yeoh, t.sheenyeoh@digipen.edu

\date		11/03/2024
\brief		Contains the defintion for the logic of the shooting element of the tower/units.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ShootingSystem.h"
#include "Application.h"

bool entityCreated = false;
bool outOfBounds = false;
EntityID hahaArrowID = 0;

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

    void ShootingSystem::Update(float deltaTime, bool shootingCheck, std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) 
    {
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
            //Entity* Arrow = entityManager.get()->GetEntity(PlayerArrowVector.front().first); // Could be second?? didnt check
            Player->AddNewComponent(ComponentType::Stats);
            StatsComponent* PlayerStats = dynamic_cast<StatsComponent*>(Player->GetComponent(ComponentType::Stats));
            PlayerStats->health -= 1;
            // entityManager.get()->DestroyEntity(Arrow->GetID());
            PlayerArrowVector.erase(PlayerArrowVector.begin());
        }

        if (shootingCheck && !entityCreated && !tower1Destroyed)
        {
            //EntityID arrowID = entityManager->CreateEntity();
            //std::cout << "This is the arrow's ID: " << arrowID << std::endl;
            Prefab* arrowPrefab = prefabManager->GetPrefab(10);
            EntityID arrowID = entityManager->CreateEntityFromPrefab(*arrowPrefab);
            entityCreated = true;
            Arrow arrow{};
            arrow.active = true;
            arrow.entity = arrowPrefab;
            
            arrows.push_back(arrow);

            //TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(arrow.entity->GetComponent(ComponentType::Transform));
            if (!CollisionVector.empty())
            {
                Entity* Tower = entityManager.get()->GetEntity(CollisionVector.front().first); // Could be second?? didnt check
                Entity* Player = entityManager.get()->GetEntity(CollisionVector.front().second); // Could be second?? didnt check
                Entity* Arrow = entityManager.get()->GetEntity(arrowID); // Could be second?? didnt check
                Arrow->AddNewComponent(ComponentType::Transform);
                Arrow->AddNewComponent(ComponentType::Physics);
                Arrow->AddNewComponent(ComponentType::Collision);
                Arrow->AddNewComponent(ComponentType::Shooting);
                TransformComponent* TowerTransform = dynamic_cast<TransformComponent*>(Tower->GetComponent(ComponentType::Transform));
                TransformComponent* PlayerTransform = dynamic_cast<TransformComponent*>(Player->GetComponent(ComponentType::Transform));
                TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(Arrow->GetComponent(ComponentType::Transform));
                TextureComponent* ArrowTexture = dynamic_cast<TextureComponent*>(Arrow->GetComponent(ComponentType::Texture));
                ArrowTexture->textureKey = { 42, 0 };
                CollisionComponent* ArrowCollision = dynamic_cast<CollisionComponent*>(Arrow->GetComponent(ComponentType::Collision));
                ArrowCollision->layer = Layer::Arrow;
                ArrowCollision->c_Height = 0;
                ArrowCollision->c_Width = 0;
                PhysicsComponent* ArrowPhysics = dynamic_cast<PhysicsComponent*>(Arrow->GetComponent(ComponentType::Physics));
                VECTORMATH::Vec2 Vel = PlayerTransform->position - TowerTransform->position;
                ShootingComponent* ArrowShooting = dynamic_cast<ShootingComponent*>(Arrow->GetComponent(ComponentType::Shooting));
                ArrowShooting->layer = Layer::Arrow;
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

        int OOBScreenWidth, OOBScreenHeight;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &OOBScreenWidth, &OOBScreenHeight);
        float scaleX = static_cast<float>(OOBScreenWidth) / 1280.f;
        float scaleY = static_cast<float>(OOBScreenHeight) / 720.f;


        // Loop through every entity
        for (auto it1 = entities->begin(); it1 != entities->end(); ++it1) 
        {
            Entity* entity = it1->second.get();

            // Check if the entity has a TransformComponent (assuming the arrow entity has one)
            TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
            //TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

            if (transform) 
            {
                // std::cout << "This is the entity's ID: " << entity->GetID() << std::endl;

                if (entity->HasComponent(ComponentType::Shooting))     
                {
                    if (transform->position.x < (0.f - OOBScreenWidth) * scaleX || transform->position.x > (OOBScreenWidth / 2.f) * scaleX ||
                        transform->position.y < (0.f - OOBScreenHeight) * scaleY || transform->position.y > (OOBScreenHeight / 2.f) * scaleY) 
                    {
                        std::cout << "This is the arrow's ID: " << entity->GetID() << std::endl;
                        lemaoArrowID = entity->GetID();
                        outOfBounds = true;
                    }
                }

            }
        }

        if (unitArrowCollision) 
        {
            // std::cout << "check for print" << std::endl;
            std::cout << "This is the arrow's ID: " << lemaoArrowID << std::endl; // ID increasing in number
            entityManager->DestroyEntity(lemaoArrowID);
            unitArrowCollision = false;
        }

        if (outOfBounds)
        {
            // std::cout << "check for print" << std::endl;
            std::cout << "This is the arrow's ID: " << lemaoArrowID << std::endl; // ID increasing in number
            entityManager->DestroyEntity(lemaoArrowID);
            outOfBounds = false;
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