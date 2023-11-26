/******************************************************************************/
/*!
\file		PhysicsSystem.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\co         Tristan Tham Rui Hong, t.tham, 2200794

\par		a.junshengaloysius@digipen.edu
            t.tham@digipen.edu

\date		10/09/2023
\brief		Contains the definitions of the Physics of the game.

 */
 /******************************************************************************/

#include "pch.h"
#include "PhysicsSystem.h"
#include "AudioEngine.h"
#include "Application.h"

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
        // std::cout << "Physics Checking" << std::endl;
        for (int step = 0; step < currentNumberOfSteps; ++step)
        {
            for (const auto& entityPair : *entities)
            {
                Entity* entity = entityPair.second.get();


                if (entity->HasComponent(ComponentType::Transform) && (entity->HasComponent(ComponentType::Physics)) && !(entity->HasComponent(ComponentType::Pathfinding)))
                {
                    TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(entity->GetComponent(ComponentType::Transform));
                    PhysicsComponent* physicsComponent = dynamic_cast<PhysicsComponent*>(entity->GetComponent(ComponentType::Physics));

                    Rigidbody rigidbody = createRigidbodyFromPhysicsComponent(physicsComponent, transformComponent);
                    

                    //std::cout << transformComponent->position.x << " " << transformComponent->position.y << std::endl;
                    //std::cout << rigidbody.position.x << " " << rigidbody.position.y << std::endl;

                    //Store Local variables for processing
                    float previousX = transformComponent->position.x;
                    float previousY = transformComponent->position.y;

                    //// Update the Rigidbody
                    //rigidbody.update(fixedDeltaTime);

                    //// Update the entity's position based on the Rigidbody's position
                    //transformComponent->position.x = rigidbody.position.x;
                    //transformComponent->position.y = rigidbody.position.y;

                    float currentX = transformComponent->position.x;
                    float currentY = transformComponent->position.y;

                    float l_velocityX = physicsComponent->velocity.x;
                    float l_velocityY = physicsComponent->velocity.y;

                    // Update the object's position using the equations of motion
                    //l_velocityX += static_cast<float>(accelerationX * dt);
                    //l_velocityY += static_cast<float>(accelerationY * dt);

                    //currentX += static_cast<int>(l_velocityX * fixedDeltaTime);
                    //currentY += static_cast<int>(l_velocityY * fixedDeltaTime);

                    //if (entity->HasComponent(ComponentType::Collision))
                    //{
                    //    CollisionComponent* collisionComponent = dynamic_cast<CollisionComponent*>(entity->GetComponent(ComponentType::Collision));

                    //    if (collisionComponent->isColliding)
                    //    {
                    //        //Update position to previous position (Stopping)
                    //        transformComponent->position.x = previousX;
                    //        transformComponent->position.y = previousY;

                    //        physicsComponent->velocity.x = 0.0f;
                    //        physicsComponent->velocity.y = 0.0f;

                    //    }
                    //    else
                    //    {
                    //        //Update position after acceleration model
                    //        transformComponent->position.x = currentX;
                    //        transformComponent->position.y = currentY;
                    //        physicsComponent->velocity.x = l_velocityX;
                    //        physicsComponent->velocity.y = l_velocityY;
                    //    }
                    //}
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

    Rigidbody PhysicsSystem::createRigidbodyFromPhysicsComponent(PhysicsComponent* physicsComponent, TransformComponent* transformComponent) {
        return Rigidbody(
            physicsComponent->mass,
            VECTORMATH::Vec2(transformComponent->position.x, transformComponent->position.y),
            VECTORMATH::Vec2(physicsComponent->velocity.x, physicsComponent->velocity.y),
            VECTORMATH::Vec2(physicsComponent->acceleration.x, physicsComponent->acceleration.y),
            physicsComponent->friction
        );
    }
}
