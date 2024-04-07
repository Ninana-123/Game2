/******************************************************************************/
/*!
\file		SystemManager.cpp
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the definitions of the System Manager

 */
 /******************************************************************************/
#include "pch.h"
#include "SystemsManager.h"
#include "Application.h"

namespace Engine
{
	std::vector<System*> SystemsManager::all_systems;

	template GraphicsSystem* SystemsManager::GetSystem<GraphicsSystem>();
	template CollisionSystem* SystemsManager::GetSystem<CollisionSystem>();
	template PhysicsSystem* SystemsManager::GetSystem<PhysicsSystem>();
	template PathfindingSystem* SystemsManager::GetSystem<PathfindingSystem>();
	template ScriptSystem* SystemsManager::GetSystem<ScriptSystem>();

	template void SystemsManager::ToggleSystemState<CollisionSystem>();
	template void SystemsManager::ToggleSystemState<GraphicsSystem>();
	template void SystemsManager::ToggleSystemState<PhysicsSystem>();
	template void SystemsManager::ToggleSystemState<PathfindingSystem>();
	template void SystemsManager::ToggleSystemState<ScriptSystem>();

	SystemsManager::SystemsManager(std::shared_ptr<Engine::AssetManager> assetManager, std::shared_ptr<Engine::EntityManager> entityManager)
		: assetManager(assetManager), entityManager(entityManager) {
	}

	void SystemsManager::Initialize()
	{
		//add systems into systems container
		all_systems.push_back(new CollisionSystem());
		all_systems.push_back(new PhysicsSystem());
		all_systems.push_back(new GraphicsSystem(assetManager, entityManager));
		all_systems.push_back(new PathfindingSystem());
		all_systems.push_back(new ScriptSystem(entityManager));

		//initialize each system
		for (auto system : all_systems)
		{
			system->Initialize();
		}
	}

	void SystemsManager::UpdateSystems(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
	{
		for (auto system : all_systems)
		{
			if (system->GetSystemState() == SystemState::On)
			{
				// If the application is paused, update only the GraphicsSystem.
				if (isPaused && system->returnSystem() == "graphics" || system->returnSystem() == "scriptSystem")
				{
					if (system->returnSystem() == "graphics")
					{
						GraphicsSystem* graphicsSystem = dynamic_cast<GraphicsSystem*>(system);
						if (graphicsSystem)
						{
							graphicsSystem->StartTimer();
							graphicsSystem->Update(entities);
							graphicsSystem->StopTimer();
							break; // Break out of the loop after updating the GraphicsSystem.
						}
					}
					else if (system->returnSystem() == "scriptSystem")
					{
						ScriptSystem* scriptSystem = dynamic_cast<ScriptSystem*>(system);
						if (scriptSystem)
						{
							scriptSystem->StartTimer();
							scriptSystem->Update(entities);
							scriptSystem->StopTimer();
							break; // Break out of the loop after updating the scriptsystem.
						}
					}
				}
				else // If the application is not paused, update all systems as usual.
				{
					system->StartTimer();
					system->Update(entities);
					system->StopTimer();
				}
			}
		}

	}

	template <typename T>
	T* SystemsManager::GetSystem()
	{
		for (System* system : all_systems)
		{
			if (dynamic_cast<T*>(system) != nullptr)
			{
				return static_cast<T*>(system);
			}
		}
		// Handle error case (e.g., system not found)
		throw std::runtime_error("System not found");
	}

	template <typename T>
	void SystemsManager::SetSystemState(SystemState newState)
	{
		for (System* system : all_systems)
		{
			if (dynamic_cast<T*>(system) != nullptr)
			{
				system->SetSystemState(newState);
				return; // Exit the loop after finding and setting the state
			}
		}
		// Handle error case (e.g., system not found)
		throw std::runtime_error("System not found");
	}

	template <typename T>
	void SystemsManager::ToggleSystemState()
	{
		for (System* system : all_systems)
		{
			if (dynamic_cast<T*>(system) != nullptr)
			{
				SystemState currentState = system->GetSystemState();
				// Toggle the state
				if (currentState == SystemState::On)
				{
					system->SetSystemState(SystemState::Off);
				}
				else
				{
					system->SetSystemState(SystemState::On);
				}
				return; // Exit the loop after finding and toggling the state
			}
		}
		// Handle error case (e.g., system not found)
		throw std::runtime_error("System not found");
	}

	std::unordered_map<std::string, double> SystemsManager::DisplaySystemTimes(double loop) {
		std::unordered_map<std::string, double> systemTimes;

		for (auto system : all_systems) {
			double systemTime = system->GetElapsedTime();
			double percentage = (systemTime / loop) * 100.0;
			std::string systemName = typeid(*system).name(); // or any other way to get the system name
			systemTimes[systemName] = percentage;
		}
		return systemTimes;
	}


	void SystemsManager::ResetSystemTimers()
	{
		for (auto system : all_systems)
		{
			system->ResetTimer();
		}
	}

	SystemsManager* SystemsManager::instance = nullptr;

	SystemsManager& SystemsManager::GetInstance()
	{
		return *instance;
	}

	void SystemsManager::DeleteInstance()
	{
		delete instance;
		instance = nullptr;
	}

}
