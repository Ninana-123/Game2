#pragma once
#include "pch.h"
#include "WindowsWindow.h"
#include "Entity.h"
#include "EntityManager.h"

namespace Engine {
    struct Config {
        std::unordered_map<std::string, std::string> properties;

        void LoadConfig(const std::string& filePath);
    };

    class Loader {
    public:
        Loader(EntityManager* entityManager) : entityManager(entityManager) {};
        ~Loader();
        // Load the scene from a data file and create entities with properties
        void LoadScene(const std::string& filePath);
        WindowProps LoadWindowPropsFromConfig(const std::string& filePath);
    private:
        Engine::EntityManager* entityManager;
    };

}