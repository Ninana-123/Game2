#pragma once
/******************************************************************************/
/*!
\file		TransformComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		10/09/2023
\brief		Contains the definitions of the Physics of the game.

 */
 /******************************************************************************/

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{

	class TransformComponent : public Component
	{
	public:
		int x = 0, y = 0;
		float scaleX =1.0f, scaleY = 1.0f;
		float rot = 0.0f;

		ComponentType GetType() const override { return ComponentType::Transform; }
		Component* Clone() const override
		{
			TransformComponent* cloneComponent = new TransformComponent();
			cloneComponent->x = x;
			cloneComponent->y = y;
			return cloneComponent;
		}
	};
}