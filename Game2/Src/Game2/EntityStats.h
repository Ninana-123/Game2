#ifndef ENTITYSTATS_H
#define ENTITYSTATS_H

#include "EngineTypes.h"

namespace Engine 
{
    class Entity;
    class Stats
    {
    public:
        Stats(float initialHealth, float initialAttackPower);

        int getHealth() const;
        int getAttackPower() const;

        void setHealth(float newHealth);
        void setAttackPower(float newAttackPower);

        void displayStats() const;

        void takeDamage(int damage);

        static void AttackTarget(int damage, Entity* entity1, Entity* target);
        
    private:
        int health;
        int attackPower;
        static float attack_timer;
    };

}

#endif