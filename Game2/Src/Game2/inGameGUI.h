/******************************************************************************/
/*!
\file		inGameGUI.h
\author
\par    	email:
\date
\brief

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#ifndef INGAMEGUISYSTEM_H
#define INGAMEGUISYSTEM_H

#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "input.h"
#include "PrefabManager.h"
#include "EngineTypes.h"
#include "AssetManager.h"

// Extern to save texture for pathfinding
extern int pathfindingEntityTexture;

namespace Engine
{

    class inGameGUI
    {
    public:

        /*!
         * \brief Constructor for the inGameGUI class.
         *
         * Initializes an instance of the inGameGUI class.
         */
        inGameGUI();

        /*!
         * \brief Constructor for the inGameGUI class with additional parameters.
         *
         * Initializes an instance of the inGameGUI class with additional parameters.
         *
         * \param em A shared pointer to the EntityManager.
         * \param pm A pointer to the PrefabManager.
         */
        inGameGUI(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm) : entityManager(em), prefabManager(pm) {}

        /*!
         * \brief Sets the target entity for inGameGUI interactions.
         *
         * This function sets the target entity for inGameGUI interactions.
         *
         * \param entity A pointer to the target entity.
         */
        inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }

        /*!
         * \brief Gets the target entity for inGameGUI interactions.
         *
         * This function returns the target entity for inGameGUI interactions.
         *
         * \return A pointer to the target entity.
         */
        inline Entity* TargetEntityGetter() { return targetEntity; }

        /*!
         * \brief Initializes the inGameGUI.
         *
         * This function initializes the inGameGUI, including the CollisionSystem and other required components.
         */
        void Initialize();

        /*!
         * \brief Updates the inGameGUI.
         *
         * This function updates the inGameGUI, including collision checking if specified.
         *
         * \param CollisionCheck A boolean indicating whether to perform collision checking during the update.
         */
        void Update(bool CollisionCheck);

        // ~inGameGUI();

    private:
        std::shared_ptr<Engine::EntityManager> entityManager;
        Engine::PrefabManager* prefabManager;
        Entity* targetEntity = nullptr;
        CollisionSystem collisionSystem;  // Declare an instance of CollisionSystem
        TextureComponent* textureCheck;

    };
}
#endif