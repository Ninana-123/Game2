/******************************************************************************/
/*!
\file		CutScene.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		10/03/2024
\brief		Contains the declarations of the Game Scene.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_CUT_SCENE_H
#define ENGINE_CUT_SCENE_H

#include "Scene.h"
#include "Loader.h"
#include "EntityManager.h"

namespace Engine {
    class CutScene : public Scene {
    public:
        /*!
        \brief Constructor for CutScene class.
        \param EM Pointer to the EntityManager instance.
        \param prefabManager Pointer to the PrefabManager instance.
        \param AM Pointer to the AssetManager instance.
        */
        CutScene(std::shared_ptr<EntityManager> EM, PrefabManager* prefabManager, std::shared_ptr<AssetManager> AM) : cutsceneLoader(EM, prefabManager, AM) {}

        /*!
        \brief Called when the cutscene is loaded.
        */
        void OnLoad() override;

        /*!
        \brief Called when the cutscene is shut down.
        */
        void OnShutDown() override;

    private:
        Loader cutsceneLoader;
        EntityManager c_entityManager;
        std::vector<TextureComponent> cutsceneTextures;
        int textureDisplayDuration; // Define this if it's supposed to control the display duration of each texture

        void ReadCutsceneTextures();

        void PlayCutscene();

        void DisplayTexture(const TextureComponent& texture);
    };
}
#endif // ENGINE_CUT_SCENE_H
