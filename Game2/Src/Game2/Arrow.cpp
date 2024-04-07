/******************************************************************************/
/*!
\file		Arrow.cpp
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
#include "Arrow.h"
#include "Application.h"
#include "Archer.h"
#include "Tower.h"

namespace Engine
{
	Arrow::Arrow(Entity* _target, float _damage ,VECTORMATH::Vec2 startingPosition) : target(_target), position(startingPosition)
	{
		//Create Arrow entity
		EM = g_ScriptFactory->GetScriptSystem()->QueryEM();
		PM = EM->QueryPM();
		Prefab* arrowPrefab = PM->GetPrefab("Arrow");
		EntityID arrowID = EM->CreateEntityFromPrefab(*arrowPrefab);
		arrow = EM->GetEntity(arrowID);
		damage = _damage;

		TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(arrow->GetComponent(ComponentType::Transform));
		if (transformComponent)
		{
			transformComponent->position = startingPosition;
		}

		TransformComponent* targetTransformComponent = dynamic_cast<TransformComponent*>(target->GetComponent(ComponentType::Transform));
		if (targetTransformComponent)
		{
			target_position = targetTransformComponent->position;
		}
		
	}

	Arrow::~Arrow()
	{
		EM->DestroyEntity(arrow->GetID());
	}

	void Arrow::Update()
	{
		if (!target || !arrow)
		{
			return;
		}
		

		dir = target_position - position;
	
		float distanceToMove = speed * static_cast<float>(fixedDeltaTime);
		//std::cout << "Distance left by arrow: " << std::sqrt(dir.x * dir.x + dir.y * dir.y) << std::endl;


		if ((std::sqrt(dir.x * dir.x + dir.y * dir.y)) <= distanceToMove)
		{
			std::cout << "Arrow Hit " << std::endl;
			Damage();
			hit = true;
			
			return;
		}

		position += dir * distanceToMove;

		//Update Arrow Entity position
		TransformComponent* transformComponent1 = dynamic_cast<TransformComponent*>(arrow->GetComponent(ComponentType::Transform));
		transformComponent1->rot = atan2(dir.y, dir.x);
		transformComponent1->position = position;
	}

	bool Arrow::Hit()
	{
		return hit;
	}

	void Arrow::Damage()
	{
		ScriptComponent* scriptComponent = dynamic_cast<ScriptComponent*>(target->GetComponent(ComponentType::Script));
		// Attempt to cast the base script pointer to the relevant derived class
		if (Archer* archer = dynamic_cast<Archer*>(scriptComponent->GetScript()))
		{
			// If the cast is successful, it means the script is an Archer
			// Now you can access Archer-specific functions or data members
			archer->hp -= damage;
			std::cout << "Minus Damage: " << damage << std::endl;
			std::cout << "Archer HP: " << archer->hp << std::endl;
		}
		else if (Tower* tower = dynamic_cast<Tower*>(scriptComponent->GetScript()))
		{
			// If the cast is successful, it means the script is a Tower
			// Now you can access Tower-specific functions or data members
			tower->hp -= damage;
			std::cout << "Minus Damage: " << damage << std::endl;
			std::cout << "Tower HP: " << tower->hp << std::endl;
		}
		else
		{
			// If neither cast succeeds, the script is neither Archer nor Tower
			// Handle this case as needed
		}
		
	}
}

