/******************************************************************************/
/*!
\file		PhysicsSystem.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		10/09/2023
\brief		Contains the declarations of the Physics of the game.

 */
 /******************************************************************************/
#ifndef ENGINE_PHYSICSSYSTEM_H
#define ENGINE_PHYSICSSYSTEM_H

#include "System.h"
#include "Entity.h"
#include "PhysicsComponent.h"
#include "Body.h"

namespace Engine
{
    class PhysicsSystem : public System
    {
    public:
        /**************************************************************************/
        /*!
        \brief Constructor for the PhysicsSystem class.

        This constructor initializes a PhysicsSystem object with default position, velocity, and acceleration values.

        */
        /**************************************************************************/
        PhysicsSystem();

        // Setters for velocity and acceleration
        /**************************************************************************/
        /*!
        \brief Sets the velocity of the physics system.

        \param[in] vx
            The velocity in the x-axis.

        \param[in] vy
            The velocity in the y-axis.

        */
        /**************************************************************************/
        void setVelocity(float vx, float vy);

        virtual std::string returnSystem() override;

        /**************************************************************************/
        /*!
        \brief Sets the acceleration of the physics system.

        \param[in] ax
            The acceleration in the x-axis.

        \param[in] ay
            The acceleration in the y-axis.

        */
        /**************************************************************************/
        void setAcceleration(float ax, float ay);

        /**************************************************************************/
        /*!
        \brief Updates the object's position based on physics calculations.

        \param[in] entities
             A pointer to an unordered_map of EntityID and unique_ptr to Entity objects.

        */
        /**************************************************************************/
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

        // Getters for position, velocity, and acceleration
        /**************************************************************************/
        /*!
        \brief Gets the x-coordinate of the object's position.

        \return
            The x-coordinate of the object's position.

        */
        /**************************************************************************/
        float getX() const;

        /**************************************************************************/
        /*!
        \brief Gets the y-coordinate of the object's position.

        \return
            The y-coordinate of the object's position.

        */
        /**************************************************************************/
        float getY() const;

        /**************************************************************************/
        /*!
        \brief Gets the velocity in the x-axis.

        \return
            The velocity in the x-axis.

        */
        /**************************************************************************/
        float getVelocityX() const;

        /**************************************************************************/
        /*!
        \brief Gets the velocity in the y-axis.

        \return
            The velocity in the y-axis.

        */
        /**************************************************************************/
        float getVelocityY() const;

        /**************************************************************************/
        /*!
        \brief Gets the acceleration in the x-axis.

        \return
            The acceleration in the x-axis.

        */
        /**************************************************************************/
        float getAccelerationX() const;

        /**************************************************************************/
        /*!
        \brief Gets the acceleration in the y-axis.

        \return
            The acceleration in the y-axis.

        */
        /**************************************************************************/
        float getAccelerationY() const;

    private:
        float x, y;            // Position
        float velocityX, velocityY; // Velocity
        float accelerationX, accelerationY; // Acceleration

        // Add a member variable for the Rigidbody object
        Rigidbody createRigidbodyFromPhysicsComponent(PhysicsComponent* physicsComponent, TransformComponent* transformComponent);
    };
}
#endif ENGINE_PHYSICSSYSTEM_H