#include "pch.h"
#include "SystemsManager.h"


namespace Engine
{
	std::vector<System*> SystemsManager::all_systems;

	void SystemsManager::Initialize()
	{
		//add systems into systems container
		all_systems.push_back(new TestSystem());
		//all_systems.push_back(new Graphics());
		all_systems.push_back(new Graphics());

		//initialize each system
		for (auto system : all_systems)
		{
			system->Initialize();
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

	void SystemsManager::UpdateSystems(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities)
	{

		for (auto system : all_systems)
		{
			system->Update(entities);
		}

	}

}
