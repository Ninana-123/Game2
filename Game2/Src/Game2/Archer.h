/******************************************************************************/
/*!
\file		Archer.h
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

	class Archer : public Script
	{
	public:
		Archer(Entity* entity_);
		void Update() override;
		void Shoot(Entity* entity);
		bool Target();
		void IsDead();

		float hp = 30.f;
		float damage = 5.f;
	private:
		
		float range = 200.f;
		bool alive = true;
		int count = 0;
		float firerate = 0.3f;
		float counter = 0.f;

		Entity* entity = nullptr;
		Entity* target = nullptr;

		TransformComponent* entityTransform = nullptr;
		ScriptComponent* entityScript = nullptr;
		TextureComponent* entityTexture = nullptr;

		std::vector<Arrow*> arrows;
		std::vector<Entity*> targets;
	
		std::shared_ptr<EntityManager> EM = nullptr;
		PrefabManager* PM = nullptr;
	};
}
