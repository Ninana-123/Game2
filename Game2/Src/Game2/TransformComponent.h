/******************************************************************************/
/*!
\file		TransformComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		9/09/2023
\brief		Contains the interface of the Transform Component

 */
 /******************************************************************************/
#pragma once

#include "Component.h"
#include "EngineTypes.h"
#include "Vector2d.h"

namespace Engine
{
	class TransformComponent : public Component
	{
	public:
		VECTORMATH::Vector2D position = VECTORMATH::Vector2D(0, 0); // Initialize position with (0, 0)

		float scaleX = 1.0f, scaleY = 1.0f;
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
			cloneComponent->position = position;
			cloneComponent->scaleX = scaleX;
			cloneComponent->scaleY = scaleY;
			cloneComponent->rot = rot;
			return cloneComponent;
		}

		/*!*****************************************************************

		\brief
		Serializes the TextureComponent data.

		\param outputStream The output stream to write the data to.

		********************************************************************/
		void Serialize(std::ostream& outputStream) const override {
			outputStream << "Position: " << position.x << ' ' << position.y << '\n';
			outputStream << "ScaleX: " << scaleX << '\n';
			outputStream << "ScaleY: " << scaleY << '\n';
			outputStream << "Rotation: " << rot << '\n';
		}

		/*!*****************************************************************

		\brief
		Deserializes the TextureComponent data.

		\param inputStream The input stream to read the data from.

		********************************************************************/
		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			inputStream >> temp >> position.x >> position.y; // Assuming format is "Position: x y"
			inputStream >> temp >> scaleX;
			inputStream >> temp >> scaleY;
			inputStream >> temp >> rot;
		}
	};
}