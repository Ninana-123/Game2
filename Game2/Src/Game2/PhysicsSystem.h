#pragma once
#include "System.h"
#include "Entity.h"
#include "PhysicsComponent.h"

namespace Engine
{
    class PhysicsSystem : public System
    {
    public:
        PhysicsSystem();

        // Setters for velocity and acceleration
        void setVelocity(float vx, float vy);
        void setAcceleration(float ax, float ay);

        // Update the object's position based on physics calculations
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

        // Getters for position, velocity, and acceleration
        float getX() const;
        float getY() const;
        float getVelocityX() const;
        float getVelocityY() const;
        float getAccelerationX() const;
        float getAccelerationY() const;

    private:
        float x, y;            // Position
        float velocityX, velocityY; // Velocity
        float accelerationX, accelerationY; // Acceleration
    };
}
