/******************************************************************************/
/*!
\file		ComponentFactory.cpp
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
    // Constructor for ComponentFactory
    ComponentFactory::ComponentFactory()
    {
        // Register components with predefined ComponentType values
        RegisterComponent(ComponentType::Transform,     []()    { return std::make_unique<TransformComponent>();       });
        RegisterComponent(ComponentType::Collision,     []()    { return std::make_unique<CollisionComponent>();       });
        RegisterComponent(ComponentType::Texture,       []()    { return std::make_unique<TextureComponent>();         });
        RegisterComponent(ComponentType::Physics,       []()    { return std::make_unique<PhysicsComponent>();         });
        RegisterComponent(ComponentType::Sprite,        []()    { return std::make_unique<SpriteComponent>();          });
        RegisterComponent(ComponentType::Pathfinding,   []()    { return std::make_unique<PathfindingComponent>();     });
        RegisterComponent(ComponentType::Logic,         []()    { return std::make_unique<BehaviourComponent>();       });
        RegisterComponent(ComponentType::Stats,         []()    { return std::make_unique<StatsComponent>();           });
        RegisterComponent(ComponentType::Shooting,      []()    { return std::make_unique<ShootingComponent>();         });
        RegisterComponent(ComponentType::Script,        []()    { return std::make_unique<ScriptComponent>();          });

    }

    // Static function to access the componentRegistry
    std::unordered_map<ComponentType, ComponentFactory::CreationFunction>& ComponentFactory::componentRegistry()
    {
        static std::unordered_map<ComponentType, CreationFunction> registry;
        return registry;
    }

    // Register a component type with its creation function
    void ComponentFactory::RegisterComponent(ComponentType type, CreationFunction function)
    {
        componentRegistry()[type] = function;
    }

    // Create a component of the specified type
    std::unique_ptr<Component> ComponentFactory::CreateComponent(ComponentType type)
    {
        auto it = componentRegistry().find(type);
        if (it != componentRegistry().end())
        {
            return it->second();
        }
        return nullptr; // Handle unknown component types or add appropriate error handling
    }

    // Convert a string to a ComponentType
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
            {"Logic",       ComponentType::Logic      },
            {"Stats",       ComponentType::Stats      },
            {"Shooting",    ComponentType::Shooting   },
            {"Script",      ComponentType::Script     },
        };

        auto it = StringTotypeMap.find(typeString);
        if (it != StringTotypeMap.end()) {
            return it->second;
        }

        // Return invalid ComponentType if not found
        return ComponentType::Unknown;
    }

    // Convert a ComponentType to a string
    std::string ComponentFactory::ComponentTypeToString(ComponentType type)
    {
        // Map enum values to component type strings
        static std::unordered_map<ComponentType, std::string> typeToStringMap =
        {
            {ComponentType::Transform,   "Transform"   },
            {ComponentType::Collision,   "Collision"   },
            {ComponentType::Physics,     "Physics"     },
            {ComponentType::Texture,     "Texture"     },
            {ComponentType::Sprite,      "Sprite"      },
            {ComponentType::Pathfinding, "Pathfinding" },
            {ComponentType::Logic,       "Logic"       },
            {ComponentType::Stats,       "Stats"       },
            {ComponentType::Shooting,    "Shooting"    },
            {ComponentType::Script,      "Script"      },
        };

        auto it = typeToStringMap.find(type);
        if (it != typeToStringMap.end()) {
            return it->second;
        }

        // Return "Unknown Component" for an invalid ComponentType
        return "Unknown Component";
    }
}