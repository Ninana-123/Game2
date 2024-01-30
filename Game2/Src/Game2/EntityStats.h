#pragma once

#ifndef ENTITYSTATS_H
#define ENTITYSTATS_H

#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "input.h"
#include "PrefabManager.h"
#include "EngineTypes.h"
#include "AssetManager.h"

namespace Engine 
{
    class Stats
    {
    public:
        Stats(float initialHealth, float initialAttackPower)
            : health(initialHealth), attackPower(initialAttackPower) {}

        int getHealth() const { return health; }
        int getAttackPower() const { return attackPower; }

        void setHealth(float newHealth) { health = newHealth; }
        void setAttackPower(float newAttackPower) { attackPower = newAttackPower; }

        void displayStats() const
        {
            std::cout << "Health: " << health << std::endl;
            std::cout << "Attack Power: " << attackPower << std::endl;
        }

        void takeDamage(int damage)
        {
            health -= damage;
            if (health < 0) {
                health = 0;
            }
            std::cout << "Took " << damage << " damage. Current health: " << health << std::endl;
        }

    private:
        int health;
        int attackPower;
    };

}

#endif