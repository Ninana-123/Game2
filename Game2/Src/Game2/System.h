//System.h 
#include "pch.h"
#include "Entity.h"

#pragma once

namespace Engine
{
	///System is a pure virtual base class (which is to say, an interface) that is
	///the base class for all systems used by the game. 
	class System
	{
		std::vector<System> all_systems;
	public:
		///Systems can receive all message send to the Core. 
		///See Message.h for details.
		//virtual void SendMessage(Message* message) { UNREFERENCED_PARAMETER(message); };

		///All systems provide a string name for debugging.
		//virtual std::string GetName() = 0;

		///All systems are updated every game frame.
		virtual void Update(Entity& entity) = 0;

		///Initialize the system.
		virtual void Initialize() {};

		///All systems need a virtual destructor to have their destructor called 
		virtual ~System() {}
	};
}