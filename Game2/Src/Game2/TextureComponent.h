/******************************************************************************/
/*!
\file		TextureComponent.h
\author		Tristan Tham Rui Hong
\par		t.tham@digipen.edu
\date		10/09/2023
\brief		Contains the interface of the Texture Component

 */
 /******************************************************************************/
#ifndef ENGINE_TEXTURECOMPONENT_H
#define ENGINE_TEXTURECOMPONENT_H

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{
	class TextureComponent : public Component
	{
	public:

		TextureKey textureKey = { 0, 0 };

		inline void SetAnimation(int subkey)
		{
			textureKey = { textureKey.mainIndex, subkey };
		}

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
			cloneComponent->textureKey = textureKey;
			return cloneComponent;
		}

		/*!*****************************************************************

		\brief
		Serializes the TextureComponent data.

		\param outputStream The output stream to write the data to.

		********************************************************************/
		void Serialize(std::ostream& outputStream) const override {
			outputStream << "MainIndex: " << textureKey.mainIndex << '\n';
			outputStream << "SubIndex: " << textureKey.subIndex << '\n';
		}

		/*!*****************************************************************

		\brief
		Deserializes the TextureComponent data.

		\param inputStream The input stream to read the data from.

		********************************************************************/
		void Deserialize(std::istream& inputStream) override {
			std::string temp;
			int mainIndex = 0;
			int subIndex = 0;
			inputStream >> temp >> mainIndex;
			inputStream >> temp >> subIndex;
			textureKey = { mainIndex, subIndex };
		}
	};
}
#endif ENGINE_TEXTURECOMPONENT_H