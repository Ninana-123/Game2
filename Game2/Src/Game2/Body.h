/******************************************************************************/
/*!
\file		Body.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807

\par		a.junshengaloysius@digipen.edu

\date		17/09/2023
\brief		Contains the delarations of the Rigidbody.

 */
 /******************************************************************************/
#ifndef ENGINE_BODY_H
#define ENGINE_BODY_H

#include "Vector2d.h"
#include "CollisionComponent.h"

class Rigidbody {
public:
    float mass;
    VECTORMATH::Vec2 position;
    VECTORMATH::Vec2 velocity;
    VECTORMATH::Vec2 acceleration;
    float friction;
    VECTORMATH::Vec2 force_accumulator;

    /**************************************************************************/
    /*!
    \brief Constructor for a rigid body with specified properties, including mass, position, velocity, acceleration, restitution, and friction.

    \param[in] mass
    The mass of the rigid body.

    \param[in] position
    The initial position of the rigid body as a 2D vector.

    \param[in] velocity
    The initial velocity of the rigid body as a 2D vector.

    \param[in] acceleration
    The initial acceleration of the rigid body as a 2D vector.

    \param[in] restitution
    The coefficient of restitution for the rigid body.

    \param[in] friction
    The friction coefficient for the rigid body.

    */
    /**************************************************************************/
    Rigidbody(float mass, VECTORMATH::Vec2 position, VECTORMATH::Vec2 velocity, VECTORMATH::Vec2 acceleration, float friction);

    /**************************************************************************/
    /*!
    \brief Apply a force to the rigid body, altering its acceleration.

    \param[in] force
    The force to be applied as a 2D vector.

    */
    /**************************************************************************/
    void apply_force(VECTORMATH::Vec2 force);

    /**************************************************************************/
    /*!
    \brief Update the state of the rigid body over a specified time step.

    \param[in] time_step
    The time step for the update.

    */
    /**************************************************************************/
    void update(double time_step);

    /**************************************************************************/
    /*!
    \brief Handle collisions between the current rigid body and another rigid body.

    \param[in] other_object
    The other rigid body involved in the collision.

    */
    /**************************************************************************/
    // void handle_collision(Rigidbody& other_object);

    /**************************************************************************/
    /*!
    \brief Sets the position of the entity.

    \param[in] pos
    The new position represented by a 2D vector.

    */
    /**************************************************************************/
    void setPosition(VECTORMATH::Vec2 pos);
};

#endif ENGINE_BODY_H