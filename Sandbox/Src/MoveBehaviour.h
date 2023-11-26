#pragma once

#include "Game2/BehaviourFCT.h"
#include "Game2/TransformComponent.h"
namespace Game {

    class MoveBehaviour : public Engine::BehaviourFCT {
    private:
        Engine::TransformComponent* transform;
        float targetX;
        float speed;

    public:
        // Constructor initializes the behavior with the Transform component of the entity and the speed of movement.
        MoveBehaviour(Engine::TransformComponent* transform, float speed)
            : transform(transform), targetX(400.0f), speed(speed) {
            // Start at position 0
            if (this->transform) {
                this->transform->position.x = 0.0f;
            }
        }

        // Initialize the behaviour (if there's anything to initialize)
        void Initialize() override {
            // If there's any initialization required, it would go here.
        }

        // Update the entity's position
        void Update() override {
            if (transform) {
                // Move the entity's x position towards the targetX
                if (transform->position.x < targetX) {
                    transform->position.x += speed;

                    // Clamp the value to the targetX if it overshoots
                    if (transform->position.x > targetX) {
                        transform->position.x = targetX;
                    }
                }
            }
        }
    };

}
