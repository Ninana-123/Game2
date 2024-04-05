/******************************************************************************/
/*!
\file		CutSceneLevel.cpp
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		10/03/2024
\brief		Contains the implementation of the Cut Scene Level.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "CutSceneLevel.h"
#include "Input.h"
#include "GameScene.h"

namespace Engine {
    const std::chrono::milliseconds TextureDisplayTime(2000); // Display each texture for 2 seconds
    const std::string CutSceneFilePath = "Resource/Scenes/CutScene.txt";
    std::chrono::steady_clock::time_point startTime{};
    bool timeToFade{ false };
    bool soundPlayed{ false };
    Input c_KeyInput;

    void CutSceneLevel::OnLoad()
    {
        cutsceneLoader.LoadScene(CutSceneFilePath);
    }

    void CutSceneLevel::OnInit()
    {
        //start an internal timer
        startTime = std::chrono::steady_clock::now();
    }

    void CutSceneLevel::OnUpdate(double deltaTime)
    {
        //check for current time
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

        if (elapsedTime.count() % 4) // Update every frame for 2 seconds
        {
            auto entities = c_entityManager.GetEntities();

            // Display entities sequentially with a delay
            auto displayEntities = [this, &entities, deltaTime]() {
                for (const auto& pair : *entities) {
                    EntityID entityID = pair.first;
                    c_entityManager.AddToStorage(entityID);
                    std::this_thread::sleep_for(TextureDisplayTime);
                }
            };

            // Start a new thread to display entities
            std::thread displayThread(displayEntities);

            // Detach the thread to allow it to continue running independently
            displayThread.detach();

            // once the fade / pan is completed
            if (vfx.FadedOut())
            {
                std::this_thread::sleep_for(std::chrono::seconds(1));
                //++currEnt;
                vfx.FadedOut() = false;
                startTime = std::chrono::steady_clock::now();
            }
        }
        
        ////skip cut scene to go level 1
        //if (c_KeyInput.IsKeyTriggered(KEY_N))
        //{
        //    cutsceneLoader.LoadScene(GameSceneFilePath);
        //}
    }

    void CutSceneLevel::FreeLevel()
    {
        //free the audio
    }

    //unload
    void CutSceneLevel::OnShutDown()
    {
        c_entityManager.DestroyEntitiesInStorage();
    }
}