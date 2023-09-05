//Core.cpp
#include "pch.h"
#include "Core.h"

//Core will contain all functions to initialize, update and destroy engine
//Control System componenets (Graphics, Collision)

namespace Engine
{
	//A global pointer to the core
	CoreEngine* CORE;

	CoreEngine::CoreEngine()
	{
		GameActive = true;
	}

	CoreEngine::~CoreEngine()
	{
		//Nothing for the destructor to do
	}

	void CoreEngine::Initialize()
	{
		
	}

	void CoreEngine::AddSystem(ISystem* system)
	{
		//Add a system to the core to be updated
		//every frame
		Systems.push_back(system);
	}
}