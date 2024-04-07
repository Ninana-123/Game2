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

    void ShootingSystem::Initialize() {

    }

    ShootingSystem::ShootingSystem() : entityManager(), prefabManager(), collisionSystem()
    {
    }

    void ShootingSystem::Update(float deltaTime, bool shootingCheck, std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities, AssetManager& assetManager,
        AudioEngine& audioEngine) 
    {
        while (!collisionSystem->CollisionQueue.empty())
        {
            CollisionVector.push_back(collisionSystem->CollisionQueue.front());
            collisionSystem->CollisionQueue.pop();
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
            CollisionComponent* collisionComponent1 = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
            StatsComponent* statsComponent = dynamic_cast<StatsComponent*>(entity->GetComponent(ComponentType::Stats));
            TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
            BehaviourComponent* behaviourComponent1 = dynamic_cast<BehaviourComponent*>(entity->GetComponent(ComponentType::Logic));
            ShootingComponent* shootingComponent1 = dynamic_cast<ShootingComponent*>(entity->GetComponent(ComponentType::Shooting));
            PathfindingComponent* pathfindingComponent1 = dynamic_cast<PathfindingComponent*>(entity->GetComponent(ComponentType::Pathfinding));

            if (entity->HasComponent(ComponentType::Collision)) 
            {
                if (collisionComponent1->layer == Layer::World && textureComponent->textureKey.mainIndex == 3) 
                {
                    // && !(statsComponent->playerDead)
                    if (collisionComponent1->archerShooting == true && !(collisionComponent1->archerArrowSpawned) && pathfindingComponent1->stoppedWalking == true)
                    {
                        // std::cout << "inside of archer shooting code" << std::endl;
                        //EntityID arrowID = entityManager->CreateEntity();
                        //std::cout << "This is the arrow's ID: " << arrowID << std::endl;
                        Prefab* archerArrowPrefab = prefabManager->GetPrefab(10);
                        EntityID archerArrowID = entityManager->CreateEntityFromPrefab(*archerArrowPrefab);
                        collisionComponent1->archerArrowSpawned = true;

                        //TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(arrow.entity->GetComponent(ComponentType::Transform));
                        if (!collisionComponent1->ArcherTowerVector.empty())
                        {
                            Entity* Tower = entityManager.get()->GetEntity(collisionComponent1->ArcherTowerVector.front().first); // Could be second?? didnt check
                            Entity* Player = entityManager.get()->GetEntity(collisionComponent1->ArcherTowerVector.front().second); // Could be second?? didnt check
                            Entity* ArcherArrow = entityManager.get()->GetEntity(archerArrowID); // Could be second?? didnt check
                            ArcherArrow->AddNewComponent(ComponentType::Transform);
                            ArcherArrow->AddNewComponent(ComponentType::Physics);
                            ArcherArrow->AddNewComponent(ComponentType::Collision);
                            ArcherArrow->AddNewComponent(ComponentType::Shooting);
                            TransformComponent* TowerTransform2 = dynamic_cast<TransformComponent*>(Tower->GetComponent(ComponentType::Transform));
                            TransformComponent* PlayerTransform2 = dynamic_cast<TransformComponent*>(Player->GetComponent(ComponentType::Transform));
                            TransformComponent* ArrowTransform2 = dynamic_cast<TransformComponent*>(ArcherArrow->GetComponent(ComponentType::Transform));
                            TextureComponent* ArrowTexture2 = dynamic_cast<TextureComponent*>(ArcherArrow->GetComponent(ComponentType::Texture));
                            ArrowTexture2->textureKey = { 42, 0 };
                            CollisionComponent* ArrowCollision2 = dynamic_cast<CollisionComponent*>(ArcherArrow->GetComponent(ComponentType::Collision));
                            ArrowCollision2->layer = Layer::Arrow;
                            ArrowCollision2->layerTarget = Layer::Tower;
                            ArrowCollision2->c_Height = 0;
                            ArrowCollision2->c_Width = 0;
                            PhysicsComponent* ArrowPhysics2 = dynamic_cast<PhysicsComponent*>(ArcherArrow->GetComponent(ComponentType::Physics));
                            VECTORMATH::Vec2 Vel = TowerTransform2->position - PlayerTransform2->position;
                            ShootingComponent* ArrowShooting = dynamic_cast<ShootingComponent*>(ArcherArrow->GetComponent(ComponentType::Shooting));
                            ArrowShooting->layer = Layer::Arrow;
                            /*VECTORMATH::Vector2DNormalize(Vel, Vel);*/
                            ArrowTransform2->rot = atan2(Vel.y, Vel.x);
                            ArrowPhysics2->velocity = Vel;
                            ArrowPhysics2->mass = 0.001f;
                            ArrowTransform2->position = PlayerTransform2->position;
                            //ArrowTransform2->position = {PlayerTransform2->position.x + 10, PlayerTransform2->position.y};
                            std::cout << "Player's x: " << PlayerTransform2->position.x << std::endl;
                            std::cout << "Player's y: " << PlayerTransform2->position.y << std::endl;
                            //CollisionVector.erase(CollisionVector.begin());
                            collisionComponent1->ArcherTowerVector.pop_back();

                        }
                    }

                    if (collisionComponent1->archerArrowSpawned)
                    {
                        //std::cout << "it is inside archerArrowedSpawned update to false" << std::endl;
                        collisionComponent1->arrowSpawnTimer -= deltaTime;
                        if (collisionComponent1->arrowSpawnTimer < 0)
                        {
                            std::cout << "it is inside archerArrowedSpawned update to false" << std::endl;
                            collisionComponent1->archerArrowSpawned = false;
                            collisionComponent1->arrowSpawnTimer = collisionComponent1->arrowSpawnInterval;
                        }
                    }
                }


                // Shooting from tower to unit
                if (collisionComponent1->layer == Layer::Tower)
                {
                    if (entity->HasComponent(ComponentType::Stats)) 
                    {
                        if (statsComponent->health == 0 && entity->GetID() == 7)
                        {
                            statsComponent->towerDestroyed = true;
                        }

                        if (statsComponent->health == 0 && entity->GetID() == 8)
                        {
                            statsComponent->towerDestroyed = true;
                        }

                    }

                    if (collisionComponent1->towerShooting == true && !(collisionComponent1->arrowSpawned) && !statsComponent->towerDestroyed)
                    {
                        //EntityID arrowID = entityManager->CreateEntity();
                        //std::cout << "This is the arrow's ID: " << arrowID << std::endl;
                        Prefab* arrowPrefab = prefabManager->GetPrefab(10);
                        EntityID arrowID = entityManager->CreateEntityFromPrefab(*arrowPrefab);
                        collisionComponent1->arrowSpawned = true;

                        //TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(arrow.entity->GetComponent(ComponentType::Transform));
                        if (!collisionComponent1->PlayerTowerVector.empty())
                        {

                            Entity* Tower = entityManager.get()->GetEntity(collisionComponent1->PlayerTowerVector.front().first); // Could be second?? didnt check
                            Entity* Player = entityManager.get()->GetEntity(collisionComponent1->PlayerTowerVector.front().second); // Could be second?? didnt check
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
                            ArrowCollision->layerTarget = Layer::World;
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
                            collisionComponent1->PlayerTowerVector.pop_back();
                            audioEngine.playSound(*(assetManager.getAudio(AudioKey("sound_Arrow"))));
                        }
                    }

                    if (collisionComponent1->arrowSpawned)
                    {
                        collisionComponent1->arrowSpawnTimer -= deltaTime;
                        if (collisionComponent1->arrowSpawnTimer < 0)
                        {
                            collisionComponent1->arrowSpawned = false;
                            collisionComponent1->arrowSpawnTimer = collisionComponent1->arrowSpawnInterval;
                        }
                    }
                }
            }

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
            entityManager->DestroyEntity(lemaoArrowID);
            unitArrowCollision = false;

        }
        //if (unitArrowCollision) 
        //{
        //    // std::cout << "check for print" << std::endl;
        //    // std::cout << "This is the arrow's ID: " << lemaoArrowID << std::endl; // ID increasing in number
        //    if (!arrowSpawnedByArcher) 
        //    {
        //        std::cout << "Arrow is deleting itself" << std::endl;
        //        entityManager->DestroyEntity(lemaoArrowID);
        //        unitArrowCollision = false;
        //    }
        //}

        if (outOfBounds)
        {
            // std::cout << "check for print" << std::endl;
            // std::cout << "This is the arrow's ID: " << lemaoArrowID << std::endl; // ID increasing in number
            entityManager->DestroyEntity(lemaoArrowID);
            outOfBounds = false;
        }

    }



}