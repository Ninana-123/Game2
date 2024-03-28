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
#include "GameScene.h"
#include "AudioEngine.h"

int pathfindingEntityTexture = 0;
int healthBarEntityTexture = 0;
int totalInfantry = 0;
int totalArcher = 0;
int totalTank = 0;
int prevSelectedEntityIndex;
bool isGamePaused = false;
bool inSettings = false;
bool isGameOver = false;
bool victoryScreenShown = false;
bool accessedCastle = false;
// bool entityCreated = false;
//AudioEngine audio;

namespace Engine
{

	int i = 0;
	bool inGameGUIInitialized = false;

	void inGameGUI::Initialize()
	{
		totalInfantry = 3;
		totalArcher = 2;
		totalTank = 1;
	}

	inGameGUI::inGameGUI() : entityManager(), prefabManager(), collisionSystem()
	{
	}

	void inGameGUI::Update(bool CollisionCheck, AudioEngine& /*audioEngine*/, AssetManager& assetManager)
	{
		UNREFERENCED_PARAMETER(assetManager);
		if (!(inGameGUIInitialized))
		{
			Initialize();
			inGameGUIInitialized = true;
		}


		// Logic for the GUI buttons for the spawning of entities upon click
		// Texture 8 is archer, 9 is tank, 7 is infantry
		if (CollisionCheck && isSpawned)
		{
			if (lastCollidingEntityTexture == 41)
			{
				healthBarEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
			}

			// Spawn infantry
			if (lastCollidingEntityTexture == 7 && totalInfantry > 0 && !unitHalfSpawned)
			{
				Prefab* infantryPrefab = prefabManager->GetPrefab(0);
				entityManager->CreateEntityFromPrefab(*infantryPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
				totalInfantry--;
			}

			// Spawn Archer
			if (lastCollidingEntityTexture == 8 && totalArcher > 0 && !unitHalfSpawned)
			{
				Prefab* archerPrefab = prefabManager->GetPrefab(1);
				entityManager->CreateEntityFromPrefab(*archerPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
				totalArcher--;
			}

			// Spawn Tank
			if (lastCollidingEntityTexture == 9 && totalTank > 0 && !unitHalfSpawned)
			{
				Prefab* tankPrefab = prefabManager->GetPrefab(2);
				entityManager->CreateEntityFromPrefab(*tankPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
				totalTank--;
			}

			if (unitHalfSpawned)
			{
				std::cout << "Unit ID is: " << unitID << std::endl;
				prevSelectedEntityIndex = m_ImGuiWrapper->selectedEntityIndex - 1;
				entityManager->DestroyEntity(unitID);
				if (m_ImGuiWrapper != nullptr) {
					m_ImGuiWrapper->SetTargetEntity(nullptr);
					entityManager->nextEntityID = prevSelectedEntityIndex+1; // Assuming this is how you reset your IDs
					prefabManager->nextPrefabID = prevSelectedEntityIndex +1; // Reset prefab ID counter if needed
					std::cout << "hello0";

					if (entityManager->GetEntity(prevSelectedEntityIndex) != nullptr) {
						m_ImGuiWrapper->SetTargetEntity(entityManager->GetEntity(prevSelectedEntityIndex));
					}
					std::cout << "hello1";
				}
				unitHalfSpawned = false;
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

		// Cheat code to get to victory screen + actual victory screen
		if (isGameOver && Input::IsKeyTriggered(KEY_W) || isGameOver && castleDestroyed == true && !victoryScreenShown)
		{	
			//audioEngine.pauseSound(*(assetManager.getAudio(AudioKey("sound_Slash"))));

			if (Application::TimePassed(2)) 
			{
				Prefab* victoryPrefab = prefabManager->GetPrefab(9);
				entityManager->CreateEntityFromPrefab(*victoryPrefab);
				victoryScreenShown = true;
			}
		}

		if (Input::IsKeyPressed(KEY_ENTER) && victoryScreenShown == true)
		{
			entityManager->DestroyEntity(victoryID);
			RestartGame();
		}

		// Reset flag
		CollisionCheck = false;

		//if (isShooting && !entityCreated)
		//{
		//	Prefab* arrowPrefab = prefabManager->GetPrefab(10);
		//	entityManager->CreateEntityFromPrefab(*arrowPrefab);
		//	entityCreated = true;
		//	//spawnTimer = 0.0f;
		//}

	}

	void inGameGUI::RestartGame()
	{
		// Resetting all the flags
		isGameOver = false;
		victoryScreenShown = false;
		inGameGUIInitialized = false;
		tower1Destroyed = false;
		tower2Destroyed = false;
		castleDestroyed = false;
		deleteAllEntity = true;
		shouldLoadScene = true; // Set flag indicating a scene should be loaded
		sceneToLoad = GameSceneFilePath; // Store the name of the scene to be loaded
	}

}