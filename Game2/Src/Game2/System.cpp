#include "pch.h"
#include "System.h"
#include "TestSystem.h"

namespace Engine
{
	//initialize static
	std::vector<System*> System::all_systems;

	void System::Initialize()
	{
		all_systems.emplace_back(new TestSystem());
	}

	void System::UpdateSystems(std::vector<System*>& systems, Entity& entity)
	{
		for (auto& system : systems)
		{
			system->Update(entity);
		}
	}

}

