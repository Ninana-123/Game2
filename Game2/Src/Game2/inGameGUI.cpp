#include "pch.h"
#include "inGameGUI.h"


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
		// std::cout << "inGameGUI Mouse collided with Entity " << lastCollidingEntity << std::endl;
		
		// Entity 5 is archer, 6 is tank, 9 is infantry
		if (CollisionCheck) 
		{
			Prefab* infantryPrefab = prefabManager->GetPrefab(0);
			Prefab* archerPrefab = prefabManager->GetPrefab(1);
			Prefab* tankPrefab = prefabManager->GetPrefab(2);

			if (lastCollidingEntity == 9) 
			{
				entityManager->CreateEntityFromPrefab(*infantryPrefab);
				lastCollidingEntity = 0;
			}

			else if (lastCollidingEntity == 5) 
			{
				entityManager->CreateEntityFromPrefab(*archerPrefab);
				lastCollidingEntity = 0;
			}
			
			else if (lastCollidingEntity == 6) 
			{
				entityManager->CreateEntityFromPrefab(*tankPrefab);
				lastCollidingEntity = 0;
			}

		}
		// Reset flag
		CollisionCheck = false;
		//std::cout << "After reset flag: " << CollisionCheck << std::endl;
    }




}