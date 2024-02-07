#include "pch.h"
#include "TransformComponent.h"
#include "Entity.h"
#include "EntityManager.h"
#include "ShootingSystem.h"
#include "CollisionSystem.h"

namespace Engine
{
    void ShootingSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) {
        for (const auto& it : *entities) {
            Entity* entity = it.second.get();

            if (entity->HasComponent(ComponentType::Shooting)) {
                   ShootingComponent* shootingcomponent = dynamic_cast<ShootingComponent*>(entity->GetComponent(ComponentType::Shooting));

                if (CanShoot(shootingcomponent)) {
                    Shoot(shootingcomponent);
                }
            }
        }
    }

    bool ShootingSystem::CanShoot(ShootingComponent* shootingComponent) {
        // Add your conditions here for when the entity can shoot
        // For example, you might check cooldown time, ammunition count, etc.
        // For simplicity, we'll always return true here.
        return true;
    }

    void ShootingSystem::Shoot(ShootingComponent* shootingComponent) {
        // Perform shooting action here
        // For now, we'll just print a message
        std::cout << "Shooting!" << std::endl;
    }
    
}