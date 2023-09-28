#include "pch.h"
#include "physics.h"

PhysicsObject::PhysicsObject(float initialX, float initialY)
    : x(initialX), y(initialY), velocityX(0.0f), velocityY(0.0f), accelerationX(0.0f), accelerationY(0.0f) {}

void PhysicsObject::setVelocity(float vx, float vy) {
    velocityX = vx;
    velocityY = vy;
}

void PhysicsObject::setAcceleration(float ax, float ay) {
    accelerationX = ax;
    accelerationY = ay;
}

void PhysicsObject::update(float deltaTime) {
    // Update the object's position using the equations of motion
    velocityX += accelerationX * deltaTime;
    velocityY += accelerationY * deltaTime;
    x += velocityX * deltaTime;
    y += velocityY * deltaTime;
}

float PhysicsObject::getX() const {
    return x;
}

float PhysicsObject::getY() const {
    return y;
}

float PhysicsObject::getVelocityX() const {
    return velocityX;
}

float PhysicsObject::getVelocityY() const {
    return velocityY;
}

float PhysicsObject::getAccelerationX() const {
    return accelerationX;
}

float PhysicsObject::getAccelerationY() const {
    return accelerationY;
}