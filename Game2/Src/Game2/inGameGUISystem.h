#pragma once

#ifndef INGAMEGUISYSTEM_H
#define INGAMEGUISYSTEM_H

#include "System.h"
#include "inGameGUIComponent.h"
#include "Entity.h"

namespace Engine
{
    class inGameGUISystem : public System 
    {
    public:
        /**************************************************************************/
        /*!
        \brief Update function to process pathfinding for a collection of entities.

        \param[in] entities
        A pointer to an `std::unordered_map` containing entities associated with unique IDs.

        */
        /**************************************************************************/
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

    private:

    };
}


#endif