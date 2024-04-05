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

    void VFX::FadeInEntity(Entity& target, float dt)
    {
        RenderDataComponent* renderData = dynamic_cast<RenderDataComponent*>(target.GetComponent(ComponentType::Render));
        if (renderData) {
            if (dt == 0.f || renderData->GetColor().a >= 1.f) {
                renderData->SetColor({ 1.f, 1.f, 1.f, 1.f });
                inDone = true;
                return;
            }
            else if (!inDone) {
                // Calculate the difference between the current alpha and 1
                float diff = 1.f - renderData->GetColor().a;
                float inter = speed * dt;
                renderData->SetColor(renderData->GetColor() + (inter * diff));
            }
        }
    }

    void VFX::FadeOutEntity(Entity& target, float dt)
    {
        RenderDataComponent* renderData = dynamic_cast<RenderDataComponent*>(target.GetComponent(ComponentType::Render));
        if (renderData) {
            if (dt == 0.f || renderData->GetColor().a <= 0.001f) {
                renderData->SetColor({ 1.f, 1.f, 1.f, 0.f });
                outDone = true;
                return;
            }
            else if (!outDone) {
                // Calculate the difference between the current alpha and 0
                float diff = renderData->GetColor().a;
                float inter = speed * dt;
                renderData->SetColor(renderData->GetColor() - (inter * diff));
                renderData->SetColor({ 1.f, 1.f, 1.f, std::max(0.0f, std::min(1.0f, renderData->GetColor().a)) });
            }
        }
    }

    void VFX::PanEntity(Entity& target, const VECTORMATH::Vec2& targetPos, float dt)
    {
        TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(target.GetComponent(ComponentType::Transform));
        if (transformComponent) {
            // Calculate the difference between the target position and the current position
            VECTORMATH::Vec2 diff = targetPos - transformComponent->position;

            // Check if the difference is within a small threshold to consider it done
            if (std::fabs(diff.x) < 0.001f && std::fabs(diff.y) < 0.001f)
            {
                panDone = true;
                return;
            }

            // Calculate the interpolation factor based on speed and delta time
            float inter = speed * dt;

            // Update the position of the entity towards the target position
            transformComponent->position += (inter * diff);
        }
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