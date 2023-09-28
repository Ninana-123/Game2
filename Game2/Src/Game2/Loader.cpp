#include "pch.h"
#include "Loader.h"
#include "Component.h"


namespace Engine {
    void Config::LoadConfig(const std::string& filePath) {
        std::ifstream configFile(filePath);
        if (!configFile.is_open()) {
            std::cerr << "Error: Could not open config file " << filePath << "\n";
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key, value;
            if (std::getline(iss, key, '=') && std::getline(iss, value)) {
                properties[key] = value;
            }
        }

        configFile.close();
    }


    Loader::~Loader()
    {
    }

    WindowProps Loader::LoadWindowPropsFromConfig(const std::string& filePath) {
        Config config;
        config.LoadConfig(filePath);

        // Use default values if properties are not found in the config file
        std::string title = config.properties["Title"];
        unsigned int width = std::stoi(config.properties["Width"]);
        unsigned int height = std::stoi(config.properties["Height"]);

        return WindowProps(title, width, height);
    }

    void Loader::LoadScene(const std::string& filePath) {
        std::ifstream sceneFile(filePath);
        if (!sceneFile.is_open()) {
            std::cerr << "Error: Could not open scene file " << filePath << "\n";
            return;
        }

        std::string line;
        if (std::getline(sceneFile, line)) {
            int entityCount = std::stoi(line);
            for (int i = 0; i < entityCount; ++i) {
                EntityID entity;
                Entity* entityPtr;
                entity = entityManager->CreateEntity();
                entityPtr = entityManager->GetEntity(entity);

                int x = 300, y = 300;
                float scaleX = 1.0f, scaleY = 1.0f, rot = 0;

                if (std::getline(sceneFile, line)) {
                    std::istringstream iss(line);
                    if (iss >> x >> y >> scaleX >> scaleY >> rot) {
                        // Successfully read properties from the scene file
                    }
                    else {
                        // Use default values if not enough properties are provided
                        x = 300;
                        y = 300;
                        scaleX = 1.0f;
                        scaleY = 1.0f;
                        rot = 0;
                        std::cout << "Entity " << i + 1 << " using default values due to not enough properties being provided\n";
                    }
                }

                // Always add the TransformComponent
                entityPtr->AddNewComponent(ComponentType::Transform);
                TransformComponent* transform = dynamic_cast<TransformComponent*>(entityPtr->GetComponent(ComponentType::Transform));
                transform->x = x;
                transform->y = y;
                transform->scaleX = scaleX;
                transform->scaleY = scaleY;
                transform->rot = rot;

                // Add more components as needed based on the format of your scene file
                std::cout << "Entity " << i + 1 << " created\n";
                if (entityPtr->HasComponent(ComponentType::Transform)) {
                    //std::cout << "Entity " << i + 1 << " has a transform component\n";
                }
            }
        }

        sceneFile.close();
    }
}