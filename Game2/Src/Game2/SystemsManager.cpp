#include "pch.h"
#include "SystemsManager.h"


namespace Engine
{
	std::vector<System*> SystemsManager::all_systems;

	void SystemsManager::Initialize()
	{
		all_systems.push_back(new TestSystem());
		//all_systems.push_back(new Graphics());
	}

	void SystemsManager::UpdateSystems(Entity* entity)
	{
		for (auto system : all_systems)
		{
			system->Update(entity);
		}
	}

}
