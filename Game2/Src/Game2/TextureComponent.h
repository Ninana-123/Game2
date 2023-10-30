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
#include <glm/glm.hpp> 

namespace Engine
{
	class TextureComponent : public Component
	{
	public:
		glm::vec2 textureCoordinates = glm::vec2(0.0f, 0.0f); 
		int textureIndex{};

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

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "Texture Class: " << static_cast<int>(textureClass) << '\n';
			outputStream << "Texture Type: " << static_cast<int>(textureType) << '\n';
		}
		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			int tempVal = 0;
			inputStream >> temp >> tempVal;
			textureClass = static_cast<TextureClass>(tempVal);
			tempVal = 0;
			inputStream >> temp >> tempVal;
			textureType = static_cast<TextureType>(tempVal);
		}
	};
}
