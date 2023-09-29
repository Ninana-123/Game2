/******************************************************************************/
/*!
\file		PhysicsSystem.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the definitions of the Physics of the game.

 */
 /******************************************************************************/

#include "pch.h"
#include "PhysicsSystem.h"

extern double dt;

namespace Engine
{
    // Constructor for the PhysicsSystem class.
    PhysicsSystem::PhysicsSystem()
        : x(0.0f), y(0.0f), velocityX(0.0f), velocityY(0.0f), accelerationX(0.0f), accelerationY(0.0f) {}

    // Sets the velocity of the physics system.
    void PhysicsSystem::setVelocity(float vx, float vy) {
        velocityX = vx;
        velocityY = vy;
    }

    // Sets the acceleration of the physics system.
    void PhysicsSystem::setAcceleration(float ax, float ay) {
        accelerationX = ax;
        accelerationY = ay;
    }

    // Updates the object's position based on physics calculations.
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

    // Gets the x-coordinate of the object's position.
    float PhysicsSystem::getX() const {
        return x;
    }

    // Gets the y-coordinate of the object's position.
    float PhysicsSystem::getY() const {
        return y;
    }

    // Gets the velocity of x of the object's position.
    float PhysicsSystem::getVelocityX() const {
        return velocityX;
    }

    // Gets the velocity of y of the object's position.
    float PhysicsSystem::getVelocityY() const {
        return velocityY;
    }

    // Gets the acceleration of x of the object's position.
    float PhysicsSystem::getAccelerationX() const {
        return accelerationX;
    }

    // Gets the acceleration of x of the object's position.
    float PhysicsSystem::getAccelerationY() const {
        return accelerationY;
    }
}
