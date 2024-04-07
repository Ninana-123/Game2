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
#include "Arrow.h"


namespace Engine
{
	extern ScriptFactory* g_ScriptFactory;

	class Tower : public Script
	{
	public:		
		Tower(Entity* entity_);
		void Update() override;
		void Shoot(Entity* entity);
		bool Target();
		void IsDead();
		
	private:
		float hp = 50.f;
		float range = 200.f;
		bool alive = true;
		int count = 0;
		float firerate = 0.05f;
		float counter = 0.f;

		Entity* entity = nullptr;
		Entity* target = nullptr;

		TransformComponent* entityTransform = nullptr;
		ScriptComponent* entityScript = nullptr;

		std::vector<Entity*> targets;
		std::vector<Arrow*> arrows;

		std::shared_ptr<EntityManager> EM = nullptr;
		PrefabManager* PM = nullptr;
	};
}