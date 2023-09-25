#pragma once

#ifndef PHYSICS_H
#define PHYSICS_H

class PhysicsObject {
public:
    PhysicsObject(float initialX, float initialY);

    // Setters for velocity and acceleration
    void setVelocity(float vx, float vy);
    void setAcceleration(float ax, float ay);

    // Update the object's position based on physics calculations
    void update(float deltaTime);

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

#endif // PHYSICS_H