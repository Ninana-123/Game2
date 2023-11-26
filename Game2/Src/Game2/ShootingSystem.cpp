#include "pch.h"
#include "ShootingSystem.h"

//namespace Engine {
//    void ShootingSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
//    {
//        // Iterate through entities and process shooting logic
//        for (auto& entityPair : *entities)
//        {
//            Entity* entity = entityPair.second.get();
//
//            // Check if the entity has a shooting component
//            if (entity->HasComponent(ComponentType::Shooting))
//            {
//                // Get the ShootingComponent associated with the entity
//                ShootingComponent* shootingComponent = dynamic_cast<ShootingComponent*>(entity->GetComponent(ComponentType::Shooting));
//
//                if (shootingComponent)
//                {
//                    // Process shooting logic for the entity
//                    ProcessShooting(*shootingComponent);
//                }
//            }
//        }
//
//        // Additional update logic as needed
//    }
//
//    void ShootingSystem::ProcessShooting(ShootingComponent& shootingComponent)
//    {
//        // Check if the entity is eligible to shoot based on some condition (e.g., cooldown, ammo, etc.)
//        if (shootingComponent.CanShoot())
//        {
//            // Perform shooting logic
//            std::cout << "Entity " << shootingComponent.GetEntityID() << " is shooting!" << std::endl;
//
//            // Subtract ammo or update cooldown, depending on your game's logic
//            shootingComponent.DecreaseAmmo(); // Example: Decrease ammo
//            shootingComponent.ResetCooldown(); // Example: Reset cooldown
//
//            // Spawn projectiles or perform other shooting-related actions
//            // ...
//
//            // Set any flags or perform actions related to shooting
//            shootingComponent.SetShootingFlag(true);
//        }
//    }
//}