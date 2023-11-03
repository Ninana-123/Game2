#include "pch.h"
#include "Body.h"

extern float dt;


Rigidbody::Rigidbody(float mass, VECTORMATH::Vec2 position, VECTORMATH::Vec2 velocity, VECTORMATH::Vec2 acceleration, float restitution, float friction)
    : mass(mass),
    position(position),
    velocity(velocity),
    acceleration(acceleration),
    restitution(restitution),
    friction(friction) {

    // Initialize force_accumulator to (0.0f, 0.0f)
    force_accumulator = VECTORMATH::Vec2(0.0f, 0.0f);

}

void Rigidbody::apply_force(VECTORMATH::Vec2 force) {
    // Apply a force to the object
    force_accumulator = force_accumulator + force;
}

void Rigidbody::update(float time_step) {
    // Update the object's position and velocity based on the applied forces and time step
    // Calculate acceleration using F = ma
    VECTORMATH::Vec2 object_acceleration = force_accumulator / mass;

    // Update velocity using v = u + at (initial velocity + acceleration * time)
    velocity = velocity + object_acceleration * time_step;

    // Update position using s = ut + 0.5at^2 (initial position + velocity * time + 0.5 * acceleration * time^2)
    position = position + velocity * time_step + 0.5f * object_acceleration * time_step * time_step;

    // Apply friction to the velocity (optional)
    velocity = velocity - velocity * friction * time_step;

    // Clear the force accumulator for the next frame
    force_accumulator = VECTORMATH::Vec2(0.0f, 0.0f);
}

void Rigidbody::handle_collision(Rigidbody& other_object) {
    // Insert collision response with another object here (e.g., apply forces to both objects)
}







