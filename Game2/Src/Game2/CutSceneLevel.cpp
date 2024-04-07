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
    size_t currentEntityIndex {0};

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
        auto currentTime = std::chrono::steady_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::seconds>(currentTime - startTime);

        if (elapsedTime.count() % 400000) // Update every frame for 2 seconds
        {
            // Load the cutscene entities from the file
            if (cutsceneEntities.empty())
            {
                cutsceneLoader.LoadScene(CutSceneFilePath);
            }

            // Ensure there are entities left to display
            if (currentEntityIndex < cutsceneEntities.size())
            {
                Entity& currentEntity = cutsceneEntities[currentEntityIndex];

                // Perform fading or panning based on the current entity's index
                vfx.FadeInEntity(currentEntity, static_cast<float>(deltaTime));

                // Increment the current entity index
                ++currentEntityIndex;

                // Reset the timer
                startTime = std::chrono::steady_clock::now();
            }
        }

        // Skip the cutscene and go to the next level if space is pressed or if the scene is finished
        if (c_KeyInput.IsKeyTriggered(GLFW_KEY_SPACE) || currentEntityIndex >= cutsceneEntities.size())
        {
            // Go to the next level
            cutsceneLoader.LoadScene(GameSceneFilePath);
        }
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