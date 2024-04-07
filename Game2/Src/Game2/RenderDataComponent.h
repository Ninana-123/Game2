/****************************************************************************** /
/*!
\file		RenderDataComponent.h
\author		Kwok Jun Lin Wayne, k.junlinwayne, 2200751
\par		k.junlinwayne@digipen.edu
\date		25/03/2024
\brief		Contains the information about the colour used for rendering.

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

	/**************************************************************************//**
	 * \brief The RenderDataComponent class.
	 *
	 * This class represents the Render Data Component, which contains information
	 * about the color used for rendering.
	 *****************************************************************************/
	class RenderDataComponent : public Component {

	public:
		float r{}, g{}, b{}, a{};

		/**************************************************************************//**
		 * \brief Set the color for rendering.
		 * \param color The color to set.
		 *****************************************************************************/
		void SetColor(glm::vec4 color)
		{
			m_Color = color;
		}

		/**************************************************************************//**
		 * \brief Get the current color used for rendering.
		 * \return The current color.
		 *****************************************************************************/
		glm::vec4& GetColor() { return m_Color; };

		/**************************************************************************//**
		 * \brief Get the type of the component.
		 * \return The type of the component.
		 *****************************************************************************/
		ComponentType GetType() const override { return ComponentType::Render; }

		/**************************************************************************//**
		 * \brief Clone the component.
		 * \return A cloned instance of the component.
		 *****************************************************************************/
		Component* Clone() const override
		{
			RenderDataComponent* cloneComponent = new RenderDataComponent();
			cloneComponent->r = r;
			cloneComponent->g = g;
			cloneComponent->b = b;
			cloneComponent->a = a;
			return cloneComponent;
		}

		/**************************************************************************//**
		 * \brief Serialize the component.
		 * \param outputStream The output stream to serialize to.
		 *****************************************************************************/
		void Serialize(std::ostream& outputStream) const override
		{
			outputStream << "Color: " << r << " " << g << " " << b << " " << a << "\n";
		}

		/**************************************************************************//**
		 * \brief Deserialize the component.
		 * \param inputStream The input stream to deserialize from.
		 *****************************************************************************/
		void Deserialize(std::istream& inputStream) override
		{
			std::string temp;
			inputStream >> temp >> r >> g >> b >> a;
		}

	private:
		glm::vec4 m_Color{}; ///< The color for texture.
	};
}
#endif // ENGINE_RENDERCOMPONENT_H