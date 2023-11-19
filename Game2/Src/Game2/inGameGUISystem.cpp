#include "pch.h"
#include "inGameGUISystem.h"
#include "TransformComponent.h"

namespace Engine
{

    void inGameGUISystem::Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
    {
        std::cout << "KONICHIWA" << std::endl;

        // Iterate through entities that require pathfinding updates.
        for (const auto& it : *entities)
        {
            Entity* entity = it.second.get();


            if (entity->HasComponent(ComponentType::inGameGUI))
            {
                //std::cout << "KONICHIWA" << std::endl;
                inGameGUIComponent* inGameComponent = dynamic_cast<inGameGUIComponent*>(entity->GetComponent(ComponentType::inGameGUI));
                
                
            }
        }
    }




}