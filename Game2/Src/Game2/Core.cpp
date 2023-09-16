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
	
	}

	void CoreEngine::Update()
	{
		while (GameActive)
		{
			//game loop
		}
	}

}