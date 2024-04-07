/******************************************************************************/
/*!
\file		CutSceneLevel.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		10/03/2024
\brief		Contains the declarations of the Cut Scene Level.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_CUTSCENE_LEVEL_H
#define ENGINE_CUTSCENE_LEVEL_H

#include "Scene.h"
#include "Loader.h"
#include "EntityManager.h"
#include "VFX.h"

namespace Engine
{
    extern const std::string CutSceneFilePath;

    class CutSceneLevel : public Scene {
    public:
        /*!
        \brief Constructor for CutScene class.
        \param EM Pointer to the EntityManager instance.
        \param prefabManager Pointer to the PrefabManager instance.
        \param AM Pointer to the AssetManager instance.
        */
        CutSceneLevel(std::shared_ptr<EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<AssetManager> AM) : cutsceneLoader(EM, prefabManager, AM) {}

        /*!
        \brief Called when the cutscene is loaded.
        */
        void OnLoad() override;

        void OnInit() override;

        void OnUpdate(double deltaTime) override;

        void FreeLevel() override;

        /*!
        \brief Called when the cutscene is shut down.
        */
        void OnShutDown() override;

    private:
        std::vector<Entity> cutsceneEntities;
        Loader cutsceneLoader;
        EntityManager c_entityManager;
        VFX vfx;
    };
}

#endif ENGINE_CUTSCENE_LEVEL_H