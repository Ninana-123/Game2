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
		//virtual initialize function
		virtual void Initialize() {}

		//virtual update function
		virtual void Update(Entity* entity) {}

		//virtual destructor
		virtual ~System() {}

		
	private:
		
	};
}