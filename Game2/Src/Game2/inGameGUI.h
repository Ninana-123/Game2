/******************************************************************************/
/*!
\file		inGameGUI.h
\author     Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		06/11/2023
\brief		Contains the declarations for the logic of the in game UI

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_INGAMEGUISYSTEM_H
#define ENGINE_INGAMEGUISYSTEM_H

#include "TransformComponent.h"
#include "CollisionComponent.h"
#include "CollisionSystem.h"
#include "input.h"
#include "PrefabManager.h"
#include "EngineTypes.h"
#include "AssetManager.h"

// Global variables
extern int pathfindingEntityTexture;
extern int healthBarEntityTexture;
extern int totalInfantry;
extern int totalArcher;
extern int totalTank;
extern bool isGamePaused;
extern bool inSettings;
extern bool isGameOver;

namespace Engine
{

    class inGameGUI
    {
    public:

        /**************************************************************************/
        /*!
        \brief Default constructor for the in-game GUI.
        */
        /**************************************************************************/
        inGameGUI();

        /**************************************************************************/
        /*!
        \brief Parameterized constructor for the in-game GUI.

        \param[in] em
        A shared pointer to the EntityManager.

        \param[in] pm
        A pointer to the PrefabManager.
        */
        /**************************************************************************/
        inGameGUI(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm) : entityManager(em), prefabManager(pm) {}

        /**************************************************************************/
        /*!
        \brief Sets the target entity for the in-game GUI.

        \param[in] entity
        Pointer to the target entity.
        */
        /**************************************************************************/
        inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }

        /**************************************************************************/
        /*!
        \brief Gets the target entity for the in-game GUI.

        \return
        Pointer to the target entity.
        */
        /**************************************************************************/
        inline Entity* TargetEntityGetter() { return targetEntity; }

        /**************************************************************************/
        /*!
        \brief Initializes the in-game GUI.
        */
        /**************************************************************************/
        void Initialize();

        /**************************************************************************/
        /*!
        \brief Updates the in-game GUI.

        \param[in] CollisionCheck
        Flag indicating whether collision checks should be performed.
        */
        /**************************************************************************/
        void Update(bool CollisionCheck, AudioEngine& audioEngine, AssetManager& assetManager);

        void RestartGame();

        // ~inGameGUI();

    private:
        std::shared_ptr<Engine::EntityManager> entityManager;
        Engine::PrefabManager* prefabManager;
        Entity* targetEntity = nullptr;
        CollisionSystem collisionSystem;  // Declare an instance of CollisionSystem

    };
}
#endif ENGINE_INGAMEGUISYSTEM_H