//System.h 
#include "pch.h"


#pragma once

namespace Engine
{
	///System is a pure virtual base class (which is to say, an interface) that is
	///the base class for all systems used by the game. 
	class Entity;
	class System
	{
	public:
	
		//Update function for child class systems
		virtual void Update(Entity* entity) = 0;

		virtual ~System() {}

		
	private:
		
	};
}