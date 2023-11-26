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
        /*!
        \brief
        Constructor for the Entity class.

        \param id
        The unique identifier for the entity.
        */
        Entity(EntityID id) : id(id) {}

        /*!
        \brief
        Destructor for the Entity class.
        */
        ~Entity() { components.clear(); }

        /*!**********************************************************************
        \brief
        Adds a component to the entity.
        \param
        component to add
        *************************************************************************/
        void AddComponent(std::unique_ptr<Component> component);

        /*!**********************************************************************
        \brief
        Adds a new component of the specified type to the entity.
        \param
        type of component to add
        *************************************************************************/
        void AddNewComponent(ComponentType type);

        /*!**********************************************************************
        \brief
        GetComponent of entity
        \param
        type of component to get
        *************************************************************************/
        Component* GetComponent(ComponentType type) const;

        /*!**********************************************************************
        \brief
        GetComponents from map
        *************************************************************************/
        std::unordered_map<ComponentType, Component*> GetComponents() const;

        /*!**********************************************************************
        \brief
        check for component
        \return
        true if have
        *************************************************************************/
        bool HasComponent(ComponentType type) const;

        /*!**********************************************************************
        \brief
        Retrieves the unique identifier of the entity.

        \return
        The unique identifier of the entity.
        *************************************************************************/
        EntityID GetID() const { return id; }

        EntityID id;
        std::unordered_map<ComponentType, std::unique_ptr<Component>> components;

    private:
    };
}