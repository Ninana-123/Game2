#pragma once

//BehaviourFCT.h

namespace Engine {

    class BehaviourFCT {
    public:
        // Virtual destructor to ensure proper cleanup of derived classes
        virtual ~BehaviourFCT() = default;

        // Initialize the behaviour
        virtual void Initialize() = 0;

        // Update function to be implemented by derived classes
        virtual void Update() = 0;

    };

}
