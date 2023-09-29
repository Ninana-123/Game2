/******************************************************************************/
/*!
\file		Core.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	29/09/2923
\brief		Declares the CoreEngine class, representing the core of the 
			Game2 Engine.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
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