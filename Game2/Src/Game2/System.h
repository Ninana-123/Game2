//System.h 
#include "pch.h"
#include "EngineTypes.h"
#pragma warning(disable: 4100) // disable "unreferenced parameter" 
#pragma once

namespace Engine
{
	enum class SystemState { On, Off };
	
	class Entity;
	class System //Base class System
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
		//virtual void Initialize(const std::vector<float>& positions = {}, const std::vector<unsigned int>& indices= {}) {}
		virtual void Initialize() {}
		//virtual void Initialize(const std::vector<float>& quadPositions = {}, const std::vector<float>& linePositions = {}, const std::vector<float>& backgroundPositions = {}) {}
		//virtual update
		virtual void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) = 0;

		virtual ~System() {}

	private:
		SystemState state = SystemState::On;
		
	};
}