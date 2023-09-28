#include "pch.h"
#include "SystemsManager.h"


namespace Engine
{
	std::vector<System*> SystemsManager::all_systems;

	template GraphicsSystem& SystemsManager::GetSystem<GraphicsSystem>();
	template CollisionSystem& SystemsManager::GetSystem<CollisionSystem>();

	template void SystemsManager::ToggleSystemState<GraphicsSystem>();
	template void SystemsManager::ToggleSystemState<CollisionSystem>();

	void SystemsManager::Initialize()
	{
		//add systems into systems container
		all_systems.push_back(new CollisionSystem());
		all_systems.push_back(new GraphicsSystem());

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
				system->Update(entities);
			}
		}
	}

	template <typename T>
	T& SystemsManager::GetSystem()
	{
		for (System* system : all_systems)
		{
			if (dynamic_cast<T*>(system) != nullptr)
			{
				return *static_cast<T*>(system);
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
	
}
