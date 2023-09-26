//System.h 
#include "pch.h"
#include "System.h"
#include "TestSystem.h"
#include "Graphics.h"

#pragma once

namespace Engine
{
	///System is a pure virtual base class (which is to say, an interface) that is
	///the base class for all systems used by the game. 
	class Entity;
	class System;

	class SystemsManager
	{
	public:
		///Initialize systems
		void Initialize();

		template <typename T>
		T& GetSystem();

		//Update all systems
		static void UpdateSystems(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

		static std::vector<System*> all_systems;
	private:
		
	};
	
}