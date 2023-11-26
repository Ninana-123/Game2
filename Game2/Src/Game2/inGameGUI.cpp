/******************************************************************************/
/*!
\file		inGameGUI.cpp
\author 	
\par    	email: 
\date   	
\brief		

			Copyright (C) 2023 DigiPen Institute of Technology.
			Reproduction or disclosure of this file or its contents without the prior
			written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "inGameGUI.h"
#include "Application.h"

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

		// Assume that entity->GetComponent(ComponentType::Texture) returns a pointer to the base class Component
		Component* component = entityManager->GetEntity(lastCollidingEntityID)->GetComponent(ComponentType::Texture);

		// Use dynamic_cast to safely check and cast to TextureComponent
		TextureComponent* textureCheck = dynamic_cast<TextureComponent*>(component);

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
				std::cout << "Colliding with pause button" << std::endl;
				//isPaused = true;
				lastCollidingEntityTexture = 0;
			}

			if (lastCollidingEntityTexture == 11)
			{
				std::cout << "Colliding with play button" << std::endl;
				//isPaused = false;
				lastCollidingEntityTexture = 0;
			}

			if (lastCollidingEntityTexture == 12)
			{
				std::cout << "Colliding with settings button" << std::endl;
				lastCollidingEntityTexture = 0;
			}

		}
		// Reset flag
		CollisionCheck = false;
		
    }
}