#include "pch.h"
#include "ComponentFactory.h"

namespace Engine
{
    ComponentFactory::ComponentFactory()
    {
        // Register components with predefined ComponentType values
        RegisterComponent(ComponentType::Transform, []() { return std::make_unique<TransformComponent>(); });
        RegisterComponent(ComponentType::Position, []() { return std::make_unique<PositionComponent>(); });

    }

    std::unordered_map<ComponentType, ComponentFactory::CreationFunction>& ComponentFactory::componentRegistry()
    {
        static std::unordered_map<ComponentType, CreationFunction> registry;
        return registry;
    }

    void ComponentFactory::RegisterComponent(ComponentType type, CreationFunction function)
    {
        componentRegistry()[type] = function;
    }

    std::unique_ptr<Component> ComponentFactory::CreateComponent(ComponentType type)
    {
        auto it = componentRegistry().find(type);
        if (it != componentRegistry().end())
        {
            return it->second();
        }
        return nullptr; // Handle unknown component types or add appropriate error handling
    }
}

