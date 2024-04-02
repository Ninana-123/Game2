/******************************************************************************/
/*!
\file		VFX.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		20/03/2024
\brief		Contains the declarations of the visual effects of the cut scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_VFX_H
#define ENGINE_VFX_H

#include "Loader.h"
#include "EntityManager.h"
#include "Vector2d.h"

namespace Engine {

    class VFX {
    
    public:
        VFX() {};
        
        // Function to fade in an entity during the cutscene
        void FadeInEntity(EntityID entityID, float dt = 0);

        // Function to fade out an entity during the cutscene
        void FadeOutEntity(EntityID entityID, float dt = 0);

        // Function to pan an entity to a target position during the cutscene
        void PanEntity(EntityID entityID, const VECTORMATH::Vec2& targetPos, float dt);

        bool& FadedOut(); // return if completed fading out

        bool& FadedIn(); //return if completed fading in

        bool& pannedOut(); //return if completed panning in/out

    private:

        bool inDone{ false }, outDone{ false }, panDone{ false };
        float speed{ 6.f }; //fixed speed for now
        EntityManager g_EntityManager;
    };
}
#endif // ENGINE_VFX_H