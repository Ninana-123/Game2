#include "pch.h"
#include "Arrow.h"

namespace Engine {
	
	void ShootingSystem::Initialize() {
		spawnTimer = 0.0f;
		spawnInterval = 10.0f;
	}

	ShootingSystem::ShootingSystem() : entityManager(), prefabManager(), collisionSystem()
	{
	}

	void ShootingSystem::Update(float deltaTime, bool shootingCheck) {
		static bool entitycreated = false;
		if (shootingCheck && !entitycreated) {
			Prefab* arrowPrefab = prefabManager->GetPrefab(9);
			entityManager->CreateEntityFromPrefab(*arrowPrefab);
			entitycreated = true;
			spawnTimer = 0.0f;
		}
		if (entitycreated) {
			spawnTimer += deltaTime;
			if (spawnTimer >= spawnInterval) {
				entitycreated = false;
			}
		}
	}
}