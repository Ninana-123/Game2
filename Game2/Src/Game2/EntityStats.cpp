#include "pch.h"
#include "EntityStats.h"
#include "EntityManager.h"
#include "Application.h"

namespace Engine
{
    float Stats::attack_timer = 0.0f;

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

    void Stats::AttackTarget(int damage, Entity* entity1, Entity* target)
    {
        //StatsComponent* statsComponent1 = dynamic_cast<StatsComponent*>(entity1->GetComponent(ComponentType::Stats)); retrieve attack values in stat component
        StatsComponent * statsComponent2 = dynamic_cast<StatsComponent*>(target->GetComponent(ComponentType::Stats));
        BehaviourComponent* behaviourComponent2 = dynamic_cast<BehaviourComponent*>(target->GetComponent(ComponentType::Logic));
        if (statsComponent2)
        {
            attack_timer += fixedDeltaTime;
            if (statsComponent2->health > 0)
            {
                if (attack_timer >= 5.0f)
                {
                    statsComponent2->health -= damage;
                    attack_timer = 0.0f;
                    std::cout << "Current Health: " << statsComponent2->health << std::endl;
                }
            }
            else
            {
                if (behaviourComponent2)
                {
                    statsComponent2->health = 0;
                    behaviourComponent2->SetBehaviourState(c_state::Death);
                    std::cout << "Dead " << statsComponent2->health << std::endl;
                }    

            }  

        }
      
    }

}