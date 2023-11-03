/******************************************************************************/
/*!
\file		Loader.cpp
\author 	Tay Jun Feng Vance, Liu Xujie
\par    	email: junfengvance.t@digipen.edu\
                   lxujie@digipen.edu
\date       29/09/2023
\brief		This file contains the implementation of the Loader class, which is responsible for loading scenes
            from data files and creating entities with associated properties. It also defines the
            methods for loading configuration properties from files and creating entities based on scene data.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "Loader.h"
#include "Component.h"
#include "ComponentFactory.h"
#include <filesystem>

namespace Engine {
    void Config::LoadConfig(const std::string& filePath)
    {
        std::ifstream configFile(filePath);
        if (!configFile.is_open())
        {
            std::cout << "Current Working Directory: " << std::filesystem::current_path() << std::endl;
            std::cerr << "Error: Could not open config file " << filePath << "\n";
            std::cerr << "Stream state: " << configFile.rdstate() << "\n";
            return;
        }

        std::string line;
        while (std::getline(configFile, line))
        {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value))
            {
                properties[key] = value;
            }
        }

        configFile.close();
    }


    Loader::~Loader()
    {
    }

    WindowConfig Loader::LoadWindowPropsFromConfig(const std::string& filePath)
    {
        Config config;
        config.LoadConfig(filePath);

        // Use default values if properties are not found in the config file
        std::string title = config.properties["Title"];
        std::cout << config.properties["Width"] << std::endl;
        std::cout << config.properties["Height"] << std::endl;
        unsigned int width = std::stoi(config.properties["Width"]);
        unsigned int height = std::stoi(config.properties["Height"]);

        return WindowConfig(title, width, height);
    }

    void Loader::LoadScene(const std::string& filePath) {
        std::ifstream sceneFile(filePath);
        if (!sceneFile.is_open()) {
            std::cerr << "Error: Could not open scene file " << filePath << "\n";
            return;
        }

        int entityCount;
        sceneFile >> entityCount;
        for (int i = 0; i < entityCount; ++i) {
            EntityID entity = entityManager->CreateEntity();
            Entity* entityPtr = entityManager->GetEntity(entity);

            std::string componentType;
            while (sceneFile >> componentType && componentType != "EndEntity") {
                ComponentType type = ComponentFactory::StringToComponentType(componentType);
                entityPtr->AddNewComponent(type);
                Component* component = entityPtr->GetComponent(type);
                if (component) {
                    component->Deserialize(sceneFile);
                }
                else {
                    std::cerr << "Unknown component type: " << componentType << std::endl;
                }
            }
            std::cout << "Entity " << i + 1 << " created\n";
        }

        sceneFile.close();
    }
    
    void Loader::LoadPrefabs(const std::string& filepath)
    {
        std::ifstream PrefabFile(filepath);
        if (!PrefabFile.is_open()) {
            std::cerr << "Error: Could not open Prefab file " << filepath << "\n";
            return;
        }

        int prefabCount;
        PrefabFile >> prefabCount;
        for (int i = 0; i < prefabCount; ++i) {
            PrefabID prefab = prefabManager->CreatePrefab();
            Prefab* prefabPtr = prefabManager->GetPrefab(prefab);
            PrefabFile >> prefabPtr->name;

            std::string componentType;
            while (PrefabFile >> componentType && componentType != "EndPrefab") {
                ComponentType type = ComponentFactory::StringToComponentType(componentType);
                prefabPtr->AddNewComponent(type);
                Component* component = prefabPtr->GetComponent(type);
                if (component) {
                    component->Deserialize(PrefabFile);
                }
                else {
                    std::cerr << "Unknown component type: " << componentType << std::endl;
                }
            }
            std::cout << "Prefab: " << prefabPtr->name << " created\n";
        }

    }

    void Loader::SavePrefabs(const std::string& filepath)
    {
        std::ofstream PrefabFile(filepath);

        if (!PrefabFile.is_open()) {
            std::cerr << "Error: Could not open Prefab file " << filepath << "\n";
            return;
        }

        // Access the PrefabManager and Prefabs
        auto* prefabs = prefabManager->GetPrefabs();

        // Write the number of prefabs
        PrefabFile << prefabs->size() << '\n';

        // Iterate through prefabs and serialize each one
        for (const auto& pair : *prefabs)
        {
            // Write the prefab name
            PrefabFile << pair.second->GetName() << '\n';

            // Serialize each component in the prefab
            for (const auto& componentPair : pair.second->GetComponents())
            {
                const ComponentType type = componentPair.first;
                const Component* component = componentPair.second;

                // Write the component type
                PrefabFile << ComponentFactory::ComponentTypeToString(type) << '\n';

                // Serialize the component
                component->Serialize(PrefabFile);
            }

            // Write the end of prefab marker
            PrefabFile << "EndPrefab\n";
        }
    }

}