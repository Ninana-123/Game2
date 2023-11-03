/******************************************************************************/
/*!
\file		Entity.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	29/09/2923
\brief		Declaration of the Entity class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include "Component.h"
#include "ComponentFactory.h"

namespace Engine
{
    class System;

    class Entity
    {
    public:
        Entity(EntityID id) : id(id) {}
        ~Entity() { components.clear(); }

        void AddComponent(std::unique_ptr<Component> component);
        void AddNewComponent(ComponentType type);
        Component* GetComponent(ComponentType type) const;
        std::unordered_map<ComponentType, Component*> GetComponents() const;
        EntityID GetID() const { return id; }
        bool HasComponent(ComponentType type) const;

        EntityID id;
        std::unordered_map<ComponentType, std::unique_ptr<Component>> components;
    private:


    };
}