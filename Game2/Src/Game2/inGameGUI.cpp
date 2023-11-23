#include "pch.h"
#include "inGameGUI.h"

int pathfindingEntityTexture = 0;

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

		// Access the last colliding entity ID from the CollisionSystem
		EntityID lastCollidingEntityID = collisionSystem.GetLastCollidingEntityID();

		
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

			
			else if (lastCollidingEntityTexture == 8)
			{
				Prefab* archerPrefab = prefabManager->GetPrefab(1);
				entityManager->CreateEntityFromPrefab(*archerPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
			}
			
			
			else if (lastCollidingEntityTexture == 9)
			{
				Prefab* tankPrefab = prefabManager->GetPrefab(2);
				entityManager->CreateEntityFromPrefab(*tankPrefab);
				pathfindingEntityTexture = lastCollidingEntityTexture;
				lastCollidingEntity = 0;
				lastCollidingEntityTexture = 0;
			}

		}
		// Reset flag
		CollisionCheck = false;
		//std::cout << "After reset flag: " << CollisionCheck << std::endl;
    }




}