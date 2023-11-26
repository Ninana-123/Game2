//LogicSystem.h
#pragma once

#include "BehaviourComponent.h"
#include "BehaviourFCT.h"
#include <vector>
#include "System.h"
#include "Entity.h"
#include "BehaviourFCT.h"

#ifndef LOGICSYSTEM_H
#define LOGICSYSTEM_H

namespace Engine
{
    class LogicSystem : public System
    {
    private:
        std::vector<BehaviourFCT*> m_behaviours;
        std::vector<BehaviourComponent*> m_behaviourComponents;

    public:
        void Initialize() override;
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;
        void AddBehaviour(BehaviourFCT* behaviour);
        BehaviourFCT* GetBehaviour(unsigned int index);
        ~LogicSystem();
    };

}

#endif


