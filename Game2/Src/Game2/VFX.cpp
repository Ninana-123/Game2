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
\
namespace Engine {

    void VFX::FadeInEntity(EntityID entityID, float dt)
    {
        if (dt == 0.f || g_ECS.GetComponent<RenderData>(target).GetColor().a >= 1.f) //dont need to iterpolate, set the opacity to 0 and transition
        {
            g_ECS.GetComponent<RenderData>(target).SetColor({ 1.f,1.f,1.f,1.f });
            inDone = true;
            return;
        }
        else if (!inDone)
        {
            //calculate the difference between the current alpha and 0
            float diff = g_ECS.GetComponent<RenderData>(target).GetColor().a + 0.001f;
            float inter = speed * dt;
            g_ECS.GetComponent<RenderData>(target).GetColor().a += (inter * diff);
        }
    }

    void VFX::FadeOutEntity(EntityID entityID, float dt)
    {
        if (dt == 0.f || g_ECS.GetComponent<RenderData>(target).GetColor().a <= 0.001f) //dont need to iterpolate, set the opacity to 0 and transition
        {
            g_ECS.GetComponent<RenderData>(target).SetColor({ 1.f,1.f,1.f,0.f });
            outDone = true;
            return;
        }
        else if (!outDone)
        {
            //calculate the difference between the current alpha and 0
            float diff = g_ECS.GetComponent<RenderData>(target).GetColor().a;
            float inter = speed * dt;
            g_ECS.GetComponent<RenderData>(target).GetColor().a -= (inter * diff);

            g_ECS.GetComponent<RenderData>(target).GetColor().a = std::max(0.0f, std::min(1.0f, g_ECS.GetComponent<RenderData>(target).GetColor().a));
        }
    }

    void VFX::PanEntity(EntityID entityID, const VECTORMATH::Vec2& targetPos, float dt)
    {
        // Get the TransformComponent of the entity
        auto& transformComponent = g_ECS.GetComponent<TransformComponent>(entityID);
        
        // Calculate the difference between the target position and the current position
        VECTORMATH::Vec2 diff = targetPos - transformComponent.position;
        
        // Check if the difference is within a small threshold to consider it done
        if (std::fabs(diff.x) < 0.001f && std::fabs(diff.y) < 0.001f)
        {
            panDone = true;
            return;
        }

        // Calculate the interpolation factor based on speed and delta time
        float inter = speed * dt;

        // Update the position of the entity towards the target position
        transformComponent.position += (inter * diff);
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