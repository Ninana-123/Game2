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

// Global variables
extern int pathfindingEntityTexture;
extern bool isGamePaused;
extern bool inSettings;


namespace Engine
{

    class inGameGUI
    {
    public:

        inGameGUI();
        inGameGUI(std::shared_ptr<Engine::EntityManager> em, Engine::PrefabManager* pm) : entityManager(em), prefabManager(pm) {}
        inline void SetTargetEntity(Entity* entity) { targetEntity = entity; }
        inline Entity* TargetEntityGetter() { return targetEntity; }
        void Initialize();

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