/**************************************************************************//**
 * \file VFX.h
 * \author Kwok Jun Lin Wayne, k.junlinwayne, 2200751
 * \par k.junlinwayne@digipen.edu
 * \date 20/03/2024
 * \brief Contains the declarations of the visual effects of the cut scene.
 *
 * Copyright (C) 2024 DigiPen Institute of Technology.
 * Reproduction or disclosure of this file or its contents
 * without the prior written consent of DigiPen Institute of
 * Technology is prohibited.
 *****************************************************************************/

#ifndef ENGINE_VFX_H
#define ENGINE_VFX_H

#include "Loader.h"
#include "Entity.h"
#include "Vector2d.h"
#include "TransformComponent.h"
#include "RenderDataComponent.h"

namespace Engine {

    /**
     * \class VFX
     * \brief Handles visual effects for the cut scene.
     *
     * This class handles visual effects such as fading in/out and panning
     * entities during the cut scene.
     */
    class VFX {

    public:

        /**
         * \brief Fades in an entity during the cut scene.
         * \param target The entity to fade in.
         * \param dt The delta time for the fade effect.
         */
        void FadeInEntity(Entity& target, float dt = 0);

        /**
         * \brief Fades out an entity during the cut scene.
         * \param target The entity to fade out.
         * \param dt The delta time for the fade effect.
         */
        void FadeOutEntity(Entity& target, float dt = 0);

        /**
         * \brief Pans an entity to a target position during the cut scene.
         * \param target The entity to pan.
         * \param targetPos The target position to pan to.
         * \param dt The delta time for the pan effect.
         */
        void PanEntity(Entity& target, const VECTORMATH::Vec2& targetPos, float dt);

        /**
         * \brief Gets the status of fading out.
         * \return The status of fading out.
         */
        bool& FadedOut(); // return if completed fading out

        /**
         * \brief Gets the status of fading in.
         * \return The status of fading in.
         */
        bool& FadedIn(); //return if completed fading in

        /**
         * \brief Gets the status of panning in/out.
         * \return The status of panning in/out.
         */
        bool& pannedOut(); //return if completed panning in/out

    private:

        bool inDone{ false }, outDone{ false }, panDone{ false }; ///< Flags indicating the completion of fade in/out and panning.
        float speed{ 6.f }; ///< Fixed speed for panning.
    };
}
#endif // ENGINE_VFX_H