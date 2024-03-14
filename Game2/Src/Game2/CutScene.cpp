/******************************************************************************/
/*!
\file		CutScene.cpp
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

#include "pch.h"
#include "CutScene.h"

const std::string CutSceneFilePath = "Resource/Scenes/CutScene.txt";

namespace Engine {

    void CutScene::OnLoad()
    {
        cutsceneLoader.LoadScene(CutSceneFilePath);
        auto entities = c_entityManager.GetEntities();
        for (const auto& pair : *entities) {
            c_entityManager.AddToStorage(pair.first);
        }

        // Read and store the list of textures from the cutscene file
        ReadCutsceneTextures();
    }


    void CutScene::ReadCutsceneTextures()
    {
        // Use the loader to load the cutscene file and extract texture information
        cutsceneLoader.LoadScene(CutSceneFilePath);
        auto entities = c_entityManager.GetEntities();
        for (const auto& pair : *entities) {
            Entity* entity = pair.second.get();
            TextureComponent* textureComponent = dynamic_cast<TextureComponent*>(entity->GetComponent(ComponentType::Texture));
            if (textureComponent) {
                // Store the texture information in the cutsceneTextures vector
                cutsceneTextures.push_back(*textureComponent);
            }
        }
    }

    void CutScene::PlayCutscene()
    {
        for (const auto& texture : cutsceneTextures) {
            // Display texture
            DisplayTexture(texture);
            // Delay before showing the next texture
            std::this_thread::sleep_for(std::chrono::milliseconds(textureDisplayDuration));
        }
    }

    void CutScene::DisplayTexture(const TextureComponent& texture)
    {
        // Display the texture on screen using your rendering system
    }

    void CutScene::OnShutDown()
    {
        c_entityManager.DestroyEntitiesInStorage();
    }
}