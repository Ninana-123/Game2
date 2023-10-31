#pragma once //Makes sure this header is only included once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vector2d.h"
#include "CollisionComponent.h"

class Rigidbody {
public:
    float mass;
    VECTORMATH::Vec2 position;
    VECTORMATH::Vec2 velocity;
    VECTORMATH::Vec2 acceleration;
    float restitution;
    float friction;
    VECTORMATH::Vec2 force_accumulator;

    Rigidbody(float mass, VECTORMATH::Vec2 position, VECTORMATH::Vec2 velocity, VECTORMATH::Vec2 acceleration, 
        float restitution, float friction);

    void apply_force(VECTORMATH::Vec2 force);

    void update(float time_step);

    void handle_collision(Rigidbody& other_object);
};

#endif // RIGIDBODY_H
