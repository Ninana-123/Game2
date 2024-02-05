#pragma once

#ifndef ENTITYSTATS_H
#define ENTITYSTATS_H

#include "EngineTypes.h"
#include "AssetManager.h"

namespace Engine 
{
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

    private:
        int health;
        int attackPower;
    };

}

#endif