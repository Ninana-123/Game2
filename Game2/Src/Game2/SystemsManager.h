//System.h 
#include "pch.h"
#include "System.h"
#include "GraphicsSystem.h"

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

		//Update all systems
		static void UpdateSystems(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities);

		template <typename T>
		T& GetSystem();

		template <typename T>
		void SetSystemState(SystemState newState);

		template <typename T>
		void ToggleSystemState();

		static std::vector<System*> all_systems;
	private:

	};

}