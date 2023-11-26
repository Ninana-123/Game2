/******************************************************************************/
/*!
\file		Body.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807

\par		a.junshengaloysius@digipen.edu

\date		17/10/2023
\brief		Contains the definitions of the Rigidbody.

 */
 /******************************************************************************/

#include "pch.h"
#include "Body.h"

extern float dt;


Rigidbody::Rigidbody(float mass, VECTORMATH::Vec2 position, VECTORMATH::Vec2 velocity, VECTORMATH::Vec2 acceleration, float friction = 0.5)
    : mass(mass), position(position), velocity(velocity), acceleration(acceleration), friction(friction) {
    force_accumulator = VECTORMATH::Vec2(0.0f, 0.0f);
}

void Rigidbody::apply_force(VECTORMATH::Vec2 force) {
    // Apply a force to the object
    force_accumulator = force_accumulator + force;
}

void Rigidbody::update(float time_step) {
    // Update the object's position and velocity based on the applied forces and time step
    // 1. Calculate acceleration using F = ma (Newton's second law)
    VECTORMATH::Vec2 object_acceleration = force_accumulator / mass;

    // 2. Update velocity using v = u + at (initial velocity + acceleration * time)
    velocity = velocity + object_acceleration * time_step;

    // 3. Update position using s = ut + 0.5at^2 (initial position + velocity * time + 0.5 * acceleration * time^2)
    position = position + velocity * time_step + 0.5f * object_acceleration * time_step * time_step;

    // 4. Apply friction to the velocity (optional)
    velocity = velocity - velocity * friction * time_step;

    // 5. Clear the force accumulator for the next frame
    force_accumulator = VECTORMATH::Vec2(0.0f, 0.0f);
}

void Rigidbody::handle_collision(Rigidbody& otherObject) {
    // Handle collision response with another object
}






