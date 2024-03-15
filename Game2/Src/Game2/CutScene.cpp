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

        // Display each entity sequentially with a delay
        size_t currentIndex = 0;
        bool isFirstEntity = true;
        while (currentIndex < entityIDs.size()) {
            // Display the current entity
            c_entityManager.AddToStorage(entityIDs[currentIndex]);

            // If it's the first entity, wait for a shorter delay
            if (isFirstEntity) {
                isFirstEntity = false;
                std::this_thread::sleep_for(std::chrono::milliseconds(4000)); // Adjust the delay as needed
            }
            else {
                std::this_thread::sleep_for(TextureDisplayTime); // Wait for the specified display time
            }

            // Move to the next entity
            ++currentIndex;
        }
    }


    void CutScene::OnShutDown()
    {
        c_entityManager.DestroyEntitiesInStorage();
    }
}