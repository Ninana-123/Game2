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

void Engine::Arrow::Update()
{
	if (target == NULL)
	{
		return;
	}
	TransformComponent* transformComponent = dynamic_cast<TransformComponent*>(target->GetComponent(ComponentType::Transform));
	target_position = transformComponent->position;

	dir = target_position - position;
	float thisFrame = speed * fixedDeltaTime;

	if ((std::sqrt(dir.x * dir.x + dir.y * dir.y)) <= thisFrame)
	{
		//play hit script, effects, sound.
		return;
	}

	position += dir * thisFrame;
}
