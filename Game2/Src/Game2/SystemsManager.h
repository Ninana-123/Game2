/******************************************************************************/
/*!
\file		SystemManager.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the System Manager

 */
 /******************************************************************************/

#include "pch.h"
#include "System.h"
#include "GraphicsSystem.h"
#include "PhysicsSystem.h"
#include "CollisionSystem.h"
#include "PathfindingSystem.h"
#include "LogicSystem.h"
#include "AssetManager.h"
#include "EntityManager.h"
#pragma once

namespace Engine
{
    /// System is a pure virtual base class (which is to say, an interface)
    /// that is the base class for all systems used by the game.
    class Entity;
    class System;

    /// SystemsManager is responsible for managing and coordinating the various systems in the game.
    /// It initializes and updates these systems during the game's execution.
    class SystemsManager
    {
    public:

        /*!
        * \brief
        * Constructor for SystemsManager.
        * \param assetManager
        * Shared pointer to the AssetManager.
        * \param EM
        * Shared pointer to the EntityManager.
        */
        SystemsManager(std::shared_ptr<Engine::AssetManager> assetManager, std::shared_ptr<Engine::EntityManager> EM);

        /*!
         * \brief
         * Initializes all system types and their respective initialize functions.
         */
        void Initialize();

        /*!
         * \brief
         * Updates all registered systems with the current state of entities.
         * \param entities
         * Container containing entity references.
         */
        static void UpdateSystems(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

        /*!
         * \brief
         * Retrieves a reference to a specific system in the container.
         * \tparam T
         * Type of the system.
         * \return T&
         * Reference to the specified system type.
         */
        template <typename T>
        T* GetSystem();

        /*!
         * \brief
         * Sets the state of a specific system in the container.
         * \tparam T
         * Type of the system.
         * \param newState
         * The new state to set for the system.
         */
        template <typename T>
        void SetSystemState(SystemState newState);

        /*!
          * \brief
          * Toggles the state of a specific system in the container.
          * \tparam T
          * Type of the system.
          */
        template <typename T>
        void ToggleSystemState();

        /// Container holding pointers to all registered systems.
        static std::vector<System*> all_systems;

        /*!
         * \brief
         * Displays the time spent in each system relative to the total loop time.
         * \param loopTime
         * Total loop time.
         * \return std::unordered_map<std::string, double>
         * A map containing system names and their respective time percentages.
         */
        std::unordered_map<std::string, double> DisplaySystemTimes(double loopTime);

        /*!
         * \brief
         * Resets the timers for all registered systems.
         */
        void ResetSystemTimers();

        /*!
         * \brief
         * Gets the singleton instance of SystemsManager.
         * \return SystemsManager&
         * Reference to the SystemsManager instance.
         */
        static SystemsManager& GetInstance();

        /*!
         * \brief
         * Deletes the singleton instance of SystemsManager.
         */
        void DeleteInstance();

        /*!
         * \brief
         * Checks if SystemsManager has been initialized.
         * \return bool
         * Returns true if SystemsManager is initialized, false otherwise.
         */
        static inline bool IsInitialized() {
            return instance != nullptr;
        }

    private:
        // Add any private members or helper functions if needed.
        std::shared_ptr<Engine::AssetManager> assetManager;
        std::shared_ptr<Engine::EntityManager> entityManager;
        static SystemsManager* instance;
       
    };
}  // namespace Engine