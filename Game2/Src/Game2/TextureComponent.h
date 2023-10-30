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

		TextureClass textureClass;

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
			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override {
			outputStream << "TextureClass: " << static_cast<int>(textureClass) << '\n';
		}

		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			int tempVal = 0;
			inputStream >> temp >> tempVal;
			textureClass = static_cast<TextureClass>(tempVal);
		}
	};
}
