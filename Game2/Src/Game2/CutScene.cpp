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
        // Add entities to storage when they are created
        auto entities = c_entityManager.GetEntities();
        for (const auto& pair : *entities) {
            c_entityManager.AddToStorage(pair.first);
        }
    }

    void CutScene::OnShutDown()
    {
        c_entityManager.DestroyEntitiesInStorage();
    }
}
