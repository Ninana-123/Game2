#include "pch.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ShootingSystem.h"
#include "Application.h"

bool entityCreated = false;
bool outOfBounds = false;
int lemaoArrowID = 0;

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

    void ShootingSystem::Update(float deltaTime, bool shootingCheck, std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) {
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
            // entityManager.get()->DestroyEntity(Arrow->GetID());
            PlayerArrowVector.erase(PlayerArrowVector.begin());
        }

        //if (shootingCheck && !entityCreated && (!tower1Destroyed || !tower2Destroyed))
        //{
        //    entityCreated = true;

        //    // Create a new arrow entity
        //    EntityID arrowID = entityManager->CreateEntity();        

        //    // Update the components of the arrow entity
        //    if (!CollisionVector.empty())
        //    {
        //        // Add necessary components to the arrow entity
        //        Entity* Arrow = entityManager.get()->GetEntity(arrowID);
        //        Arrow->AddNewComponent(ComponentType::Physics);
        //        Arrow->AddNewComponent(ComponentType::Collision);
        //        Arrow->AddNewComponent(ComponentType::Shooting);

        //        Entity* Tower = entityManager.get()->GetEntity(CollisionVector.front().first);
        //        Entity* Player = entityManager.get()->GetEntity(CollisionVector.front().second);
        //        TransformComponent* TowerTransform = dynamic_cast<TransformComponent*>(Tower->GetComponent(ComponentType::Transform));
        //        TransformComponent* PlayerTransform = dynamic_cast<TransformComponent*>(Player->GetComponent(ComponentType::Transform));
        //        TransformComponent* ArrowTransform = dynamic_cast<TransformComponent*>(Arrow->GetComponent(ComponentType::Transform));
        //        TextureComponent* ArrowTexture = dynamic_cast<TextureComponent*>(Arrow->GetComponent(ComponentType::Texture));
        //        ArrowTexture->textureKey = { 42, 0 };
        //        CollisionComponent* ArrowCollision = dynamic_cast<CollisionComponent*>(Arrow->GetComponent(ComponentType::Collision));
        //        ArrowCollision->layer = Layer::Arrow;
        //        ArrowCollision->c_Height = 0;
        //        ArrowCollision->c_Width = 0;
        //        PhysicsComponent* ArrowPhysics = dynamic_cast<PhysicsComponent*>(Arrow->GetComponent(ComponentType::Physics));
        //        VECTORMATH::Vec2 Vel = PlayerTransform->position - TowerTransform->position;
        //        ShootingComponent* ArrowShooting = dynamic_cast<ShootingComponent*>(Arrow->GetComponent(ComponentType::Shooting));
        //        ArrowShooting->layer = Layer::Arrow;
        //        ArrowTransform->rot = atan2(Vel.y, Vel.x);
        //        ArrowPhysics->velocity = Vel;
        //        ArrowPhysics->mass = 0.001f;
        //        ArrowTransform->position = TowerTransform->position;
        //        CollisionVector.pop_back();
        //    }
        //}

        if (shootingCheck && !entityCreated && (!tower1Destroyed || !tower2Destroyed))
        {
            //EntityID arrowID = entityManager->CreateEntity();
            //std::cout << "This is the arrow's ID: " << arrowID << std::endl;
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
                //Arrow->AddNewComponent(ComponentType::Transform);
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

        int screenWidth, screenHeight;
        glfwGetFramebufferSize(glfwGetCurrentContext(), &screenWidth, &screenHeight);
        float scaleX = screenWidth / 1280.f;
        float scaleY = screenHeight / 720.f;

        // Loop through every entity
        for (auto it1 = entities->begin(); it1 != entities->end(); ++it1) 
        {
            Entity* entity = it1->second.get();

            // Check if the entity has a TransformComponent (assuming the arrow entity has one)
            TransformComponent* transform = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
            TextureComponent* texture = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));

            if (transform) 
            {
                //// Check if the entity is an arrow and if it's out of bounds
                //if (entity->HasComponent(ComponentType::Shooting) &&
                //    (transform->position.x < 0 || transform->position.x > screenWidth ||
                //        transform->position.y < 0 || transform->position.y > screenHeight)) {

                //    // Destroy the arrow entity
                //    entityManager->DestroyEntity(entity->GetID());
                //}
                std::cout << "This is the entity's ID: " << entity->GetID() << std::endl;

                if (entity->HasComponent(ComponentType::Shooting))
                {
                    std::cout << "This is the arrow's ID: " << entity->GetID() << std::endl;
                    lemaoArrowID = entity->GetID();
                    outOfBounds = true;
                }

            }
        }

        if (outOfBounds) 
        {
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