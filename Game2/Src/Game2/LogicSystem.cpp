//LogicSystem.cpp
#include "pch.h"
#include "LogicSystem.h"
#include <iostream>
#include <memory>

namespace Engine {

    //Initializes LogicSystem
    void LogicSystem::Initialize() {
        // Initialization logic for LogicSystem
        std::cout << "LogicSystem Initialized\n";
    }

    //Update loop for LogicSystem
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

    //Adds behaviour to system
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
