/******************************************************************************/
/*!
\file		Tower.h
\author 	Tristan Tham Rui Hong
\par    	email: t.tham@digipen.edu
\date   	01/03/2924
\brief		Declaration of the ScriptSystem class

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#pragma once
#include "pch.h"
#include "ScriptSystem.h"


namespace Engine
{
	class Tower : public Script
	{
	public:		

		void Update() override;

	private:
		std::vector<Entity*> targets;
		float firerate = 1.f;
		float counter = 0.f;
	};
}