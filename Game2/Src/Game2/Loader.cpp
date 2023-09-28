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

    WindowConfig Loader::LoadWindowPropsFromConfig(const std::string& filePath) {
        Config config;
        config.LoadConfig(filePath);

        // Use default values if properties are not found in the config file
        std::string title = config.properties["Title"];
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

        std::string line;
        if (std::getline(sceneFile, line)) {
            int entityCount = std::stoi(line);
            for (int i = 0; i < entityCount; ++i) {
                EntityID entity;
                Entity* entityPtr;
                entity = entityManager->CreateEntity();
                entityPtr = entityManager->GetEntity(entity);

                bool addTransformComponent = false, addCollisionComponent = false;
                int x = 300, y = 300;

                float scaleX = 1.0f, scaleY = 1.0f, rot = 0;
                float c_Width = 30.0f, c_Height = 45.0f;
                bool isColliding = false;

                int minX = 0, minY = 0, maxX = 0, maxY = 0;

                if (std::getline(sceneFile, line)) {
                    std::istringstream iss(line);
                    if (iss >>addTransformComponent>> x >> y >> scaleX >> scaleY >> rot>> addCollisionComponent >> c_Width>>c_Height>>isColliding>>minX>>minY>>maxX>>maxY) {
                        // Successfully read properties from the scene file
                    }
                    else {
                        // Use default values if not enough properties are provided
                    }
                }

                if (addTransformComponent) {
                    entityPtr->AddNewComponent(ComponentType::Transform);
                    TransformComponent* transform = dynamic_cast<TransformComponent*>(entityPtr->GetComponent(ComponentType::Transform));
                    transform->x = x;
                    transform->y = y;
                    transform->scaleX = scaleX;
                    transform->scaleY = scaleY;
                    transform->rot = rot;
                }
                if (addCollisionComponent) {
                    entityPtr->AddNewComponent(ComponentType::Collision);
                    CollisionComponent* collision = dynamic_cast<CollisionComponent*>(entityPtr->GetComponent(ComponentType::Collision));
                    collision->c_Width = c_Width;
                    collision->c_Height = c_Height;
                }
                // Add more components as needed based on the format of your scene file
                std::cout << "Entity " << i + 1 << " created\n";
                if (entityPtr->HasComponent(ComponentType::Transform)) {
                    std::cout << "Entity " << i + 1 << " has a transform component\n";
                }
                if (entityPtr->HasComponent(ComponentType::Collision)) {
                   std::cout << "Entity " << i + 1 << " has a collision component\n";
                }
            }
        }

        sceneFile.close();
    }
}