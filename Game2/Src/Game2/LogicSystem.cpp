//LogicSystem.cpp
#include "pch.h"
#include "LogicSystem.h"
#include <iostream>
#include <memory>

namespace Engine {

    void LogicSystem::Initialize() {
        // Initialization logic for LogicSystem
        std::cout << "LogicSystem Initialized\n";
    }

    void LogicSystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) {
        for (auto& [id, entity] : *entities) {
            if (entity->HasComponent(ComponentType::Logic)) {
                auto* behaviourComponent = dynamic_cast<BehaviourComponent*>(entity->GetComponent(ComponentType::Logic));
                if (behaviourComponent) {
                    auto behaviour = GetBehaviour(behaviourComponent->GetBehaviourIndex());
                    if (behaviour) {
                        behaviour->Update();
                    }
                }
            }
        }
        //std::cout << "LogicSystem Updated\n";
    }

    void LogicSystem::AddBehaviour(BehaviourFCT* behaviour) {
        // Add a new behaviour to the system
        m_behaviours.push_back(behaviour);
    }

    BehaviourFCT* LogicSystem::GetBehaviour(unsigned int index)
    {
        if (index < m_behaviours.size()) {
            return m_behaviours[index];
        }
        return nullptr; // Return nullptr if index is out of range
    }

    LogicSystem::~LogicSystem() {
        std::cout << "LogicSystem Destroyed\n";
    }

}
