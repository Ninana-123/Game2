/******************************************************************************/
/*!
\file		Loader.h
\author 	Tay Jun Feng Vance
\par    	email: junfengvance.t@digipen.edu
\date       29/09/2023
\brief		Defines the Loader class and related structures for managing scene loading and configuration.
            This file contains the declaration of the Loader class, which is responsible for loading scenes
            from data files and creating entities with properties. It also defines the Config structure
            for managing configuration properties.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_LOADER_H
#define ENGINE_LOADER_H

#include "pch.h"
#include "WindowsWindow.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Prefab.h"
#include "PrefabManager.h"
#include "AssetManager.h"


namespace Engine {
    struct Config {
        std::unordered_map<std::string, std::string> properties;

        /*!
         * \brief Load configuration data from a file.
         * \param filePath The path to the configuration file.
         */
        void LoadConfig(const std::string& filePath);
    };

    class Loader {
    public:
        /*!
         * \brief Constructor for the Loader class.
         * \param EM Shared pointer to the EntityManager.
         * \param prefabManager Pointer to the PrefabManager.
         * \param AM Shared pointer to the AssetManager.
         */
        Loader(std::shared_ptr<Engine::EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<Engine::AssetManager> AM) : entityManager(EM), prefabManager(prefabManager), assetManager(AM) {};
        
        /*!
         * \brief Destructor for the Loader class.
         */
        ~Loader();
        /*!
         * \brief Load a scene from a data file and create entities with properties.
         * \param filePath The path to the scene data file.
         */
        void LoadScene(const std::string& filePath);

        /*!
         * \brief Load prefabs from a data file.
         * \param filepath The path to the prefab data file.
         */
        void LoadPrefabs(const std::string& filepath);

        /*!
         * \brief Save prefabs to a data file.
         * \param filepath The path to the prefab data file.
         */
        void SavePrefabs(const std::string& filepath);

        /*!
         * \brief Load window properties from a configuration file.
         * \param filePath The path to the configuration file.
         * \return WindowConfig The window configuration settings.
         */
        WindowConfig LoadWindowPropsFromConfig(const std::string& filePath);
    private:
        std::shared_ptr<Engine::EntityManager> entityManager;
        Engine::PrefabManager* prefabManager;
        std::shared_ptr<Engine::AssetManager> assetManager;
    };

}
#endif ENGINE_LOADER_H