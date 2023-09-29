#pragma once
/******************************************************************************/
/*!
\file		TextureComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		10/09/2023
\brief		Contains the interface of the Texture Component

 */
 /******************************************************************************/

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{
	class TextureComponent : public Component
	{
	public:

		TextureClass textureClass = TextureClass::Null;
		TextureType textureType = TextureType::Null;

		/*!*****************************************************************

		\brief
		Getter for this Components enum

		\return  ComponentType
		Returns an enum of the component Type

		********************************************************************/

		ComponentType GetType() const override { return ComponentType::Texture; } 

		/*!*****************************************************************

		\brief
		Cloner for this component

		\return  Component*
		Clone component with cloned data members

		********************************************************************/
		Component* Clone() const override
		{
			TextureComponent* cloneComponent = new TextureComponent();
			cloneComponent->textureClass = textureClass;
			cloneComponent->textureType = textureType;
			return cloneComponent;
		}
	};
}
