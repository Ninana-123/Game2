//System.h 
#include "pch.h"
#include "EngineTypes.h"

#pragma once

namespace Engine
{
	enum class SystemState { On, Off };
	
	class Entity;
	class System 
	{
	public:
		
		// Set the state of the system
		void SetSystemState(SystemState newState)
		{
			state = newState;
		}

		// Get the current state of the system
		SystemState GetSystemState() const
		{
			return state;
		}

		//virtual initialize
		virtual void Initialize() {}

		//virtual update
		virtual void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) = 0;

		virtual ~System() {}

	private:
		SystemState state = SystemState::On;
		
	};
}