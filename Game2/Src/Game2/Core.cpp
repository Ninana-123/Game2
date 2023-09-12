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
		
	}

	void CoreEngine::Initialize()
	{
		//Iterate and Initialize all systems in Systems container
		for (unsigned i = 0; i < Systems.size(); i++)
		{
			Systems[i]->Initialize();
		}
	}

	void CoreEngine::Update()
	{
		while (GameActive)
		{
			//game loop
		}
	}

	void CoreEngine::AddSystem(ISystem* system)
	{
		//Add a system to the core to be updated
		//every frame
		Systems.push_back(system);
	}

	void CoreEngine::ClearSystems()
	{
		for (unsigned i = 0; i < Systems.size(); i++)
		{
			delete Systems[Systems.size() - i - 1];
		}
	}

}