/******************************************************************************/
/*!
\file		inGameGUI.cpp
\author     Ang Jun Sheng Aloysius, a.junshengaloysius, 2201807
\par		a.junshengaloysius@digipen.edu
\date		06/11/2023
\brief		Contains the definitions for the logic of the in game UI

			Copyright (C) 2023 DigiPen Institute of Technology.
			Reproduction or disclosure of this file or its contents without the prior
			written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "inGameGUI.h"
#include "Application.h"

int pathfindingEntityTexture = 0;
bool isGamePaused = false;
bool inSettings = false;
bool isGameOver = false;

namespace Engine
{
	
	int i = 0;

	void inGameGUI::Initialize() 
	{

	}

	inGameGUI::inGameGUI() : entityManager(), prefabManager(), collisionSystem()
	{
	}

	void inGameGUI::Update(bool CollisionCheck)
	{

		// Logic for the GUI buttons for the spawning of entities upon click
		// Texture 8 is archer, 9 is tank, 7 is infantry
		if (CollisionCheck) 
		{	
			
			if (lastCollidingEntityTexture == 7)
			{
				Prefab* infantryPrefab = prefabManager->GetPrefab(0);
				entityManager->CreateEntityFromPrefab(*infantryPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
			}
			
			if (lastCollidingEntityTexture == 8)
			{
				Prefab* archerPrefab = prefabManager->GetPrefab(1);
				entityManager->CreateEntityFromPrefab(*archerPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
			}			
			
			if (lastCollidingEntityTexture == 9)
			{
				Prefab* tankPrefab = prefabManager->GetPrefab(2);
				entityManager->CreateEntityFromPrefab(*tankPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
			}

			// Logic for the pause/play and setting buttons
			if (lastCollidingEntityTexture == 10)
			{
				//std::cout << "Colliding with pause button" << std::endl;
				isPaused = true;
				lastCollidingEntityTexture = 0;
			}

			if (lastCollidingEntityTexture == 11)
			{
				//std::cout << "Colliding with play button" << std::endl;
				isPaused = false;
				lastCollidingEntityTexture = 0;
			}

			if (lastCollidingEntityTexture == 12)
			{
				//std::cout << "Colliding with settings button" << std::endl;
				if (inSettings) 
				{
					inSettings = false;
				}
				else 
				{
					inSettings = true;
				}
				lastCollidingEntityTexture = 0;
			}
		}

		// Cheat code to get to victory screen
		if (isGameOver && Input::IsKeyTriggered(KEY_W))
		{
			Prefab* victoryPrefab = prefabManager->GetPrefab(9);
			entityManager->CreateEntityFromPrefab(*victoryPrefab);
		}

		// Reset flag
		CollisionCheck = false;		
    }
}