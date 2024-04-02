/******************************************************************************/
/*!
\file		VFX.cpp
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		20/03/2024
\brief		Contains the implementation of the visual effects of the Cut Scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "VFX.h"

namespace Engine {

    void VFX::FadeInEntity(EntityID entityID, float dt)
    {

    }

    void VFX::FadeOutEntity(EntityID entityID, float dt)
    {

    }

    void VFX::PanEntity(EntityID entityID, const VECTORMATH::Vec2& targetPos, float dt)
    {

    }

    bool& VFX::FadedOut()
    {
        return outDone;
    }

    bool& VFX::FadedIn()
    {
        return inDone;
    }

    bool& VFX::pannedOut()
    {
        return panDone;    
    }
}