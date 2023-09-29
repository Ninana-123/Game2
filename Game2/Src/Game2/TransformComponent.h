#pragma once
/******************************************************************************/
/*!
\file		TransformComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Transform Component

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
		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Transform; }

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			TransformComponent* cloneComponent = new TransformComponent();
			cloneComponent->x = x;
			cloneComponent->y = y;
			return cloneComponent;
		}
	};
}