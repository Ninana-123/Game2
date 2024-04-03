/******************************************************************************/
/*!
\file		Tower.cpp
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptSystem class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "Tower.h"
#include "Application.h"
#include "Arrow.h"

namespace Engine
{
	void Tower::Update()
	{
		if (targets.empty())
		{
			return;
		}

		if (counter <= 0.f)
		{
			Entity* target = targets.front();
			//Shoot(target);
			counter = 1.f / firerate;
		}
		
		counter -= fixedDeltaTime;

	}

	void Tower::Shoot(Entity* target)
	{
		UNREFERENCED_PARAMETER(target);
		//call Arrow script
		//Arrow* arrow = new Arrow(target);
	}
}

