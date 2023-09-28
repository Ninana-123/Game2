#pragma once

#include "Component.h"
#include "EngineTypes.h"

namespace Engine
{
	class TextureComponent : public Component
	{
	public:

		TextureClass textureClass = TextureClass::Null;
		TextureType textureType = TextureType::Null;

		ComponentType GetType() const override { return ComponentType::Texture; } 
		Component* Clone() const override
		{
			TextureComponent* cloneComponent = new TextureComponent();
			cloneComponent->textureClass = textureClass;
			cloneComponent->textureType = textureType;
			return cloneComponent;
		}
	};
}
