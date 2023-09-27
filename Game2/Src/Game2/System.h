//System.h 
#include "pch.h"
#include "EngineTypes.h"

#pragma once

namespace Engine
{
	///System is a pure virtual base class (which is to say, an interface) that is
	///the base class for all systems used by the game. 
	class Entity;
	class System
	{
	public:
		
		virtual void Initialize() {}

		//Update function for child class systems
		virtual void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) = 0;

		virtual ~System() {}

		
	private:
		
	};
}