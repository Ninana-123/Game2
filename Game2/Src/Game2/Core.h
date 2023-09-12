//Core.h

#pragma once
#define GAME2_API __declspec(dllexport)

#include "System.h"

namespace Engine
{

	class CoreEngine
	{
	public:
		CoreEngine();
		~CoreEngine();
		void Initialize();
		void Update();
		void AddSystem(ISystem* system);
		void ClearSystems();
	private:
		std::vector<ISystem*> Systems; //container to store systems
		bool GameActive;
	};
}