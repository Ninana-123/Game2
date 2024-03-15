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

const std::chrono::milliseconds TextureDisplayTime(3000); // Display each texture for 3 seconds

namespace Engine {
const std::string CutSceneFilePath = "Resource/Scenes/CutScene.txt";

void CutScene::OnLoad()
{
    cutsceneLoader.LoadScene(CutSceneFilePath);
    auto entities = c_entityManager.GetEntities();

    // Store the entities in a vector for sequential display
    std::vector<EntityID> entityIDs;
    for (const auto& pair : *entities) {
        entityIDs.push_back(pair.first);
    }

    // Define a lambda function to display entities sequentially with a delay
    auto displayEntities = [this, &entityIDs]() {
        for (size_t i = 0; i < entityIDs.size(); ++i) {
            c_entityManager.AddToStorage(entityIDs[i]);
            std::this_thread::sleep_for(TextureDisplayTime);
        }
    };

    // Start a new thread to display entities
    std::thread displayThread(displayEntities);

    // Detach the thread to allow it to continue running independently
    displayThread.detach();
}


    void CutScene::OnShutDown()
    {
        c_entityManager.DestroyEntitiesInStorage();
    }
}