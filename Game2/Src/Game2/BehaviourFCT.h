/******************************************************************************/
/*!
\file		BehaviourFCT.h
\author 	Tristan Tham Rui Hong

\email		t.tham@digipen.edu

\date   	30/01/2024
\brief		This file contains the implementation of the states behaviours
            that the entities will be using.
Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_BEHAVIOUR_FCT_H
#define ENGINE_BEHAVIOUR_FCT_H

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
#endif ENGINE_BEHAVIOUR_FCT_H