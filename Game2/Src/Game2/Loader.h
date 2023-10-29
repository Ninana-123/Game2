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

#pragma once
#include "pch.h"
#include "WindowsWindow.h"
#include "Entity.h"
#include "EntityManager.h"
#include "Prefab.h"
#include "PrefabManager.h"

namespace Engine {
    struct Config {
        std::unordered_map<std::string, std::string> properties;

        void LoadConfig(const std::string& filePath);
    };

    class Loader {
    public:
        Loader(std::shared_ptr<Engine::EntityManager> EM, PrefabManager* prefabManager) : entityManager(EM), prefabManager(prefabManager) {};
        ~Loader();
        // Load the scene from a data file and create entities with properties
        void LoadScene(const std::string& filePath);
        void LoadPrefabs(const std::string& filepath);
        
        void SavePrefabs(const std::string& filepath);
        WindowConfig LoadWindowPropsFromConfig(const std::string& filePath);
    private:
        std::shared_ptr<Engine::EntityManager> entityManager;
        Engine::PrefabManager* prefabManager;
    };

}