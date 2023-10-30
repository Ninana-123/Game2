//System.h 
#include "pch.h"
#include "EngineTypes.h"

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
		virtual void Initialize() {}

		//virtual update
		virtual void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) = 0;

		virtual ~System() {}

		inline void StartTimer() {
			startTime = std::chrono::high_resolution_clock::now();
		}

		inline void StopTimer() {
			auto endTime = std::chrono::high_resolution_clock::now();
			elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		}

		inline double GetElapsedTime() const {
			return elapsedTime / 1000.0; // Convert to milliseconds
		}

		inline void ResetTimer() {
			elapsedTime = 0.0;
		}

	private:
		SystemState state = SystemState::On;
		std::chrono::high_resolution_clock::time_point startTime;
		double elapsedTime = 0.0;
		
	};
}