#pragma once
#include "Game2/pch.h"
#include "Game2/Component.h"


namespace Engine
{
    class System;

    class Entity 
    {
    public:
        Entity(EntityID id) : id(id) {}
        ~Entity() = default;

        void AddComponent(std::unique_ptr<Component> component);
        Component* GetComponent(ComponentType type) const;
        std::unordered_map<ComponentType, Component*> GetComponents() const;
        EntityID GetID() const { return id; }

        void Update();

    private:
        EntityID id;
        std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
        static std::vector<System*> systems;
    };

  
}