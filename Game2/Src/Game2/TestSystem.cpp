#include "pch.h"
#include "EntityManager.h"
#include "PositionComponent.h"
#include "Entity.h"
#include "Input.h"
#include "System.h"
#include "TestSystem.h"

void Engine::TestSystem::Update(Entity& entity)
{
    // Check if the entity has a PositionComponent
    if (entity.HasComponent(ComponentType::Position)) {
        // Access the PositionComponent
        PositionComponent* positionComponent = static_cast<PositionComponent*>(entity.GetComponent(ComponentType::Position));

        // Check for the "2" key press
        if (Input::IsKeyPressed(GLFW_KEY_2)) 
        {
            // Update the x and y values of the PositionComponent
            positionComponent->x += 2; // Example: Increment x by 2
            positionComponent->y += 2; // Example: Increment y by 2
        }
    }
}
