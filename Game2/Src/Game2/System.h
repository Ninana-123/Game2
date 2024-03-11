/******************************************************************************/
/*!
\file		System.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		System class declaration

 */
/******************************************************************************/
#ifndef ENGINE_SYSTEM_H
#define ENGINE_SYSTEM_H

#include "pch.h"
#include "EngineTypes.h"

namespace Engine
{
	enum class SystemState { On, Off };
	
	class Entity;
	class System //Base class System
	{
	public:
		
		/*!
		* \brief
		* Set the state of the system.
		* \param newState
		* The new state to set for the system.
		*/
		void SetSystemState(SystemState newState)
		{
			state = newState;
		}

		/*!
		 * \brief
		 * Get the current state of the system.
		 * \return SystemState
		 * Returns the current state of the system.
		 */
		SystemState GetSystemState() const
		{
			return state;
		}

		/*!
		 * \brief
		 * Virtual function to initialize the system.
		 */
		virtual void Initialize() {}

		/*!
		 * \brief
		 * Virtual function to update the system.
		 * \param entities
		 * A pointer to the map of entities to update.
		 */
		virtual void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) = 0;

		/*!
		 * \brief
		 * Virtual destructor for the System class.
		 */
		virtual ~System() {}

		/*!
		 * \brief
		 * Start the timer for measuring system update time.
		 */
		inline void StartTimer() {
			startTime = std::chrono::high_resolution_clock::now();
		}

		/*!
		 * \brief
		 * Stop the timer and accumulate elapsed time.
		 */
		inline void StopTimer() {
			auto endTime = std::chrono::high_resolution_clock::now();
			elapsedTime += std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count();
		}

		/*!
		 * \brief
		 * Get the elapsed time since starting the timer.
		 * \return double
		 * Returns the elapsed time in milliseconds.
		 */
		inline double GetElapsedTime() const {
			return elapsedTime / 1000.0; // Convert to milliseconds
		}

		/*!
		 * \brief
		 * Reset the timer to zero.
		 */
		inline void ResetTimer() {
			elapsedTime = 0.0;
		}

	private:
		SystemState state = SystemState::On;
		std::chrono::high_resolution_clock::time_point startTime;
		double elapsedTime = 0.0;		
	};
}
#endif ENGINE_SYSTEM_H