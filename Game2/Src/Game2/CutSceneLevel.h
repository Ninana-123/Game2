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
    /**
     * \brief The file path for the cut scene.
     */
    extern const std::string CutSceneFilePath;

    /**
     * \class CutSceneLevel
     * \brief Represents the Cut Scene Level.
     *
     * This class represents the Cut Scene Level and handles the loading,
     * initialization, updating, and shutdown of the cut scene.
     */
    class CutSceneLevel : public Scene {
    public:
        /**
         * \brief Constructor for the CutSceneLevel class.
         * \param EM Pointer to the EntityManager instance.
         * \param prefabManager Pointer to the PrefabManager instance.
         * \param AM Pointer to the AssetManager instance.
         */
        CutSceneLevel(std::shared_ptr<EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<AssetManager> AM) : cutsceneLoader(EM, prefabManager, AM) {}

        /**
         * \brief Called when the cut scene is loaded.
         */
        void OnLoad() override;

        /**
         * \brief Called when the cut scene is initialized.
         */
        void OnInit() override;

        /**
         * \brief Called when the cut scene is updated.
         * \param deltaTime The time since the last update.
         */
        void OnUpdate(double deltaTime) override;

        /**
         * \brief Free resources used by the cut scene.
         */
        void FreeLevel() override;

        /**
         * \brief Called when the cut scene is shut down.
         */
        void OnShutDown() override;

    private:
        std::vector<Entity> cutsceneEntities; ///< Vector of entities in the cut scene.
        Loader cutsceneLoader; ///< Loader for the cut scene.
        EntityManager c_entityManager; ///< Entity manager for the cut scene.
        VFX vfx; ///< Visual effects for the cut scene.
    };
}

#endif // ENGINE_CUTSCENE_LEVEL_H