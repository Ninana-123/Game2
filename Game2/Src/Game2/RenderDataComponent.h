/****************************************************************************** /
/*!
\file		RenderDataComponent.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/03/2024
\brief		Contains the interface of the Render data component.

Copyright (C) 2024 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents
without the prior written consent of DigiPen Institute of
Technology is prohibited.
 */
 /******************************************************************************/

#ifndef ENGINE_RENDERCOMPONENT_H
#define ENGINE_RENDERCOMPONENT_H

#include "pch.h"
#include "Component.h"
#include "EngineTypes.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

namespace Engine {

	class RenderDataComponent : public Component {

	public:
		float r{}, g{}, b{}, a{};


		void SetColor(glm::vec4 color)
		{
			m_Color = color;
		}

		glm::vec4& GetColor() { return m_Color; };

		ComponentType GetType() const override { return ComponentType::Render; }

		Component* Clone() const override
		{
			RenderDataComponent* cloneComponent = new RenderDataComponent();
			cloneComponent->r = r;
			cloneComponent->g = g;
			cloneComponent->b = b;
			cloneComponent->a = a;
			return cloneComponent;
		}

		void Serialize(std::ostream& outputStream) const override 
		{
			outputStream << "Color: " << r << " " << g << " " << b << " " << a << "\n";
		}

		void Deserialize(std::istream& inputStream) override 
		{
			std::string temp;
			inputStream >> temp >> r >> g >> b >> a;

		}

	private:
		glm::vec4 m_Color{}; //colour for texture
		
	};
}
#endif ENGINE_RENDERCOMPONENT_H