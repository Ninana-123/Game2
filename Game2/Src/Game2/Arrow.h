/******************************************************************************/
/*!
\file		Arrow.h
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

#include "ScriptSystem.h"
#include "Vector2d.h"

namespace Engine
{
	extern ScriptFactory* g_ScriptFactory;

	class Arrow
	{
	public:
		Arrow(Entity* _target, VECTORMATH::Vec2 startingPosition);
		~Arrow();
		void Update();
		bool Hit();
	private:
		Entity* arrow = nullptr;
		Entity* target = nullptr;
		std::shared_ptr<EntityManager> EM = nullptr;
		PrefabManager* PM = nullptr;
		bool hit = false;
		VECTORMATH::Vec2 position;
		VECTORMATH::Vec2 target_position;
		VECTORMATH::Vec2 dir;
		
		float speed = 9.f;
	};
}