/******************************************************************************/
/*!
\file		ComponentFactory.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	29/09/2923
\brief		Definition of the ComponentFactory class.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "ComponentFactory.h"

namespace Engine
{

    /*!**********************************************************************
    \brief
    Constructor for the ComponentFactory class
    *************************************************************************/
    ComponentFactory::ComponentFactory()
    {
        // Register components with predefined ComponentType values
        RegisterComponent(ComponentType::Transform, []()    { return std::make_unique<TransformComponent>();       });
        RegisterComponent(ComponentType::Collision, []()    { return std::make_unique<CollisionComponent>();       });
        RegisterComponent(ComponentType::Texture,   []()    { return std::make_unique<TextureComponent>();         });
        RegisterComponent(ComponentType::Physics,   []()    { return std::make_unique<PhysicsComponent>();         });
        RegisterComponent(ComponentType::Sprite,    []()    { return std::make_unique<SpriteComponent>();          });
        RegisterComponent(ComponentType::Pathfinding, []()  { return std::make_unique<PathfindingComponent>();     });

    }
    /*!**********************************************************************
    \brief
    Returns a reference to the component registry, a mapping of ComponentType to CreationFunction.
    \return
    A reference to the component registry, where ComponentType is mapped to CreationFunction.
    *************************************************************************/
    std::unordered_map<ComponentType, ComponentFactory::CreationFunction>& ComponentFactory::componentRegistry()
    {
        static std::unordered_map<ComponentType, CreationFunction> registry;
        return registry;
    }
    /*!**********************************************************************
    \brief
    Registers a component creation function for a given ComponentType.
    \param type
    The ComponentType to associate with the creation function.
    \param function 
    The creation function to register for the specified ComponentType.
    *************************************************************************/
    void ComponentFactory::RegisterComponent(ComponentType type, CreationFunction function)
    {
        componentRegistry()[type] = function;
    }
    /*!**********************************************************************
    \brief
    Creates a unique_ptr to a Component based on the specified ComponentType.
    \param type
    The ComponentType for which to create a Component.
    \return 
    A unique_ptr to the created Component or nullptr if the ComponentType is unknown.
    *************************************************************************/
    std::unique_ptr<Component> ComponentFactory::CreateComponent(ComponentType type)
    {
        auto it = componentRegistry().find(type);
        if (it != componentRegistry().end())
        {
            return it->second();
        }
        return nullptr; // Handle unknown component types or add appropriate error handling
    }

    ComponentType ComponentFactory::StringToComponentType(const std::string& typeString)
    {
        // Map component type strings to enum values
        static std::unordered_map<std::string, ComponentType> StringTotypeMap = 
        {
            {"Transform",   ComponentType::Transform  },
            {"Collision",   ComponentType::Collision  },
            {"Physics",     ComponentType::Physics    },
            {"Texture",     ComponentType::Texture    },
            {"Sprite",      ComponentType::Sprite     },
            {"Pathfinding", ComponentType::Pathfinding},
        };

        auto it = StringTotypeMap.find(typeString);
        if (it != StringTotypeMap.end()) {
            return it->second;
        }

        //return invalid
        return ComponentType::Unknown;
    }

    std::string ComponentFactory::ComponentTypeToString(ComponentType type)
    {
        // Map enum values to component type strings
        static std::unordered_map<ComponentType, std::string> typeToStringMap =
        {
            {ComponentType::Transform,  "Transform"},
            {ComponentType::Collision,  "Collision"},
            {ComponentType::Physics,    "Physics"  },
            {ComponentType::Texture,    "Texture"  },
            {ComponentType::Sprite,     "Sprite"  },
            {ComponentType::Pathfinding,"Pathfinding"  },
        };

        auto it = typeToStringMap.find(type);
        if (it != typeToStringMap.end()) {
            return it->second;
        }

        //return invalid
        return "Unknown Component";
    }

}


