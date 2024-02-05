#include "pch.h"
#include "EntityStats.h"

namespace Engine
{
    Stats::Stats(float initialHealth, float initialAttackPower)
        : health(initialHealth), attackPower(initialAttackPower) {}

    int Stats::getHealth() const 
    { 
        return static_cast<int>(health); 
    }

    int Stats::getAttackPower() const 
    { 
        return static_cast<int>(attackPower); 
    }

    void Stats::setHealth(float newHealth) 
    { 
        health = newHealth; 
    }

    void Stats::setAttackPower(float newAttackPower) 
    { 
        attackPower = newAttackPower; 
    }

    void Stats::displayStats() const
    {
        std::cout << "Health: " << getHealth() << std::endl;
        std::cout << "Attack Power: " << getAttackPower() << std::endl;
    }

    void Stats::takeDamage(int damage)
    {
        health -= damage;
        if (health < 0) 
        {
            health = 0;
        }
        std::cout << "Took " << damage << " damage. Current health: " << getHealth() << std::endl;
    }
}