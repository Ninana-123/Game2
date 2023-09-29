#include "pch.h"
#include "PhysicsSystem.h"

extern double dt;

namespace Engine
{
    PhysicsSystem::PhysicsSystem()
        : x(0.0f), y(0.0f), velocityX(0.0f), velocityY(0.0f), accelerationX(0.0f), accelerationY(0.0f) {}

    void PhysicsSystem::setVelocity(float vx, float vy) {
        velocityX = vx;
        velocityY = vy;
    }

    void PhysicsSystem::setAcceleration(float ax, float ay) {
        accelerationX = ax;
        accelerationY = ay;
    }

    void PhysicsSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) 
    {
        for (const auto& entityPair : *entities)
        {
            Entity* entity = entityPair.second.get();
            std::cout << "Physics Checking" << std::endl;

            if (entity->HasComponent(ComponentType::Transform) && (entity->HasComponent(ComponentType::Physics)))
            {
                TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
                PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(entity->GetComponent(ComponentType::Physics));

                //Store Local variables for processing
                int previousX = transformComponent->x;
                int previousY = transformComponent->y;

                int currentX = transformComponent->x;
                int currentY = transformComponent->y;

                float l_velocityX = physicsComponent->velocityX;
                float l_velocityY = physicsComponent->velocityY;

                // Update the object's position using the equations of motion
                l_velocityX += static_cast<float>(accelerationX * dt);
                l_velocityY += static_cast<float>(accelerationY * dt);

                currentX += static_cast<int>(l_velocityX * dt);
                currentY += static_cast<int>(l_velocityY * dt);

                if (entity->HasComponent(ComponentType::Collision))
                {
                    CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));
            
                    if (collisionComponent->isColliding)
                    {
                        //Update position to previous position (Stopping)
                        transformComponent->x = previousX;
                        transformComponent->y = previousY;

                        physicsComponent->velocityX = 0.0f;
                        physicsComponent->velocityY = 0.0f;

                        collisionComponent->isColliding = false;
                    }
                    else
                    {
                        //Update position after acceleration model
                        transformComponent->x = currentX;
                        transformComponent->y = currentY;
                        physicsComponent->velocityX = l_velocityX;
                        physicsComponent->velocityY = l_velocityY;
                    }
                }            
            }
        }
    }

    float PhysicsSystem::getX() const {
        return x;
    }

    float PhysicsSystem::getY() const {
        return y;
    }

    float PhysicsSystem::getVelocityX() const {
        return velocityX;
    }

    float PhysicsSystem::getVelocityY() const {
        return velocityY;
    }

    float PhysicsSystem::getAccelerationX() const {
        return accelerationX;
    }

    float PhysicsSystem::getAccelerationY() const {
        return accelerationY;
    }
}
