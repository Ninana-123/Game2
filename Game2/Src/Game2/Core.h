//Core.h

#pragma once
#define GAME2_API __declspec(dllexport)

#define BIT(x) (1<<x)
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
	
	private:
		
		bool GameActive;
	};
}