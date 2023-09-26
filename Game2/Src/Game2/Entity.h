#pragma once

#include "Component.h"


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
        bool HasComponent(ComponentType type) const;

        EntityID id;
        std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
    private:
       
    
    };
}