#include "pch.h"
#include "inGameGUI.h"


namespace Engine
{
	
	int i = 0;

	void inGameGUI::Initialize() 
	{

	}

	inGameGUI::inGameGUI() : entityManager(), prefabManager()
	{
	}

	void inGameGUI::Update(bool CollisionCheck)
	{

		std::cout << CollisionCheck << std::endl;
		if (CollisionCheck) 
		{
			//// Get the coresponding entity type
			Prefab* infantryPrefab = prefabManager->GetPrefab(0);
			Prefab* archerPrefab = prefabManager->GetPrefab(1);
			Prefab* tankPrefab = prefabManager->GetPrefab(2);
			if (i < 1) {
				entityManager->CreateEntityFromPrefab(*infantryPrefab);
				entityManager->CreateEntityFromPrefab(*archerPrefab);
				entityManager->CreateEntityFromPrefab(*tankPrefab);
				i++;
			}
		}
    }




}