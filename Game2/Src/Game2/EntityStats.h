/******************************************************************************/
/*!
\file		EntityStats.h
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807

\par		a.junshengaloysius@digipen.edu

\date		12/01/2024

\brief		Contains the declarations for keeping track and manipulation of entity stats.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENTITYSTATS_H
#define ENTITYSTATS_H

#include "EngineTypes.h"

namespace Engine 
{
    class Entity;
    class Stats
    {
    public:
        /**************************************************************************/
        /*!
        \brief Constructor for Stats class.

        \param initialHealth
            Initial health value for the entity.

        \param initialAttackPower
            Initial attack power value for the entity.
        */
        /**************************************************************************/
        Stats(float initialHealth, float initialAttackPower);

        /**************************************************************************/
        /*!
        \brief Retrieves the current health value of the entity.

        \return
        The current health value of the entity.
        */
        /**************************************************************************/
        int getHealth() const;

        /**************************************************************************/
        /*!
        \brief Retrieves the current attack power value of the entity.

        \return
        The current attack power value of the entity.
        */
        /**************************************************************************/
        int getAttackPower() const;

        /**************************************************************************/
        /*!
        \brief Sets the health value of the entity to a new value.

        \param newHealth
        The new health value to set.
        */
        /**************************************************************************/
        void setHealth(float newHealth);

        /**************************************************************************/
        /*!
        \brief Sets the attack power value of the entity to a new value.

        \param newAttackPower
        The new attack power value to set.
        */
        /**************************************************************************/
        void setAttackPower(float newAttackPower);

        /**************************************************************************/
        /*!
        \brief Displays the current statistics (health and attack power) of the entity.
        */
        /**************************************************************************/
        void displayStats() const;

        /**************************************************************************/
        /*!
        \brief Applies damage to the entity.

        \param damage
        The amount of damage to apply to the entity.
        */
        /**************************************************************************/
        void takeDamage(int damage);

        /**************************************************************************/
        /*!
        \brief Static function to perform an attack on a target entity.

        \param damage
            The amount of damage to apply to the target entity.

        \param entity1
            The entity performing the attack.

        \param target
            The target entity to attack.
        */
        /**************************************************************************/
        static void AttackTarget(int damage, Entity* entity1, Entity* target);
        
    private:
        int health;
        int attackPower;
        static float attack_timer;
    };

}

#endif