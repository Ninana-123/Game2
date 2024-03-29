/******************************************************************************/
/*!
\file		EntityStats.cpp
\author		Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\co         Tristan Tham Rui Hong, t.tham, 2200794

\par		a.junshengaloysius@digipen.edu

\date		12/01/2024

\brief		Contains the definitions for keeping track and manipulation of entity stats.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "EntityStats.h"
#include "EntityManager.h"
#include "Application.h"

namespace Engine
{
    float Stats::attack_timer = 0.0f;

    Stats::Stats(float initialHealth, float initialAttackPower)
        : health(static_cast<int>(initialHealth)), attackPower(static_cast<int>(initialAttackPower)) {}

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
        health = static_cast<int>(newHealth);
    }

    void Stats::setAttackPower(float newAttackPower)
    {
        attackPower = static_cast<int>(newAttackPower);
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
        CollisionComponent* collisionComponent1 = dynamic_cast<CollisionComponent*>(entity1->GetComponent(ComponentType::Collision));
        if (collisionComponent1->layer == Layer::Tower)
        {
            BehaviourComponent* behaviourComponent1 = dynamic_cast<BehaviourComponent*>(entity1->GetComponent(ComponentType::Logic));
            behaviourComponent1->SetBehaviourState(c_state::Static);
            //if (tower1Destroyed) 
            //{
            //    behaviourComponent1->SetBehaviourState(c_state::TowerDestroyed);
            //}
            //if (tower2Destroyed) 
            //{
            //    behaviourComponent1->SetBehaviourState(c_state::TowerDestroyed);
            //}
            return;
        }
        if (target)
        {
            StatsComponent* statsComponent2 = dynamic_cast<StatsComponent*>(target->GetComponent(ComponentType::Stats));
            BehaviourComponent* behaviourComponent2 = dynamic_cast<BehaviourComponent*>(target->GetComponent(ComponentType::Logic));
            if (statsComponent2)
            {
                if (statsComponent2->health > 0)
                {
                    // If time passed after 1 second when attacking, tower takes damage
                    if (Application::TimePassed(1))
                    {
                        statsComponent2->health -= damage;
                        std::cout << "Current Tower Health: " << statsComponent2->health << std::endl;
                    }
                }
                else
                {
                    if (behaviourComponent2)
                    {
                        statsComponent2->health = 0;
                        // behaviourComponent2->SetBehaviourState(c_state::Death);
                        std::cout << "Tower Dead " << statsComponent2->health << std::endl;
                    }
                }
            }
        }               
    }

}