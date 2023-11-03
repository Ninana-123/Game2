/******************************************************************************/
/*!
\file		VertexArray.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the VertexArray class. It
			provides functions for managing Vertex Array Objects (VAOs), adding
			vertex buffers, and setting vertex buffer layouts.

			Copyright (C) 2023 DigiPen Institute of Technology.
			Reproduction or disclosure of this file or its contents without the prior
			written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "Renderer.h"

/*!
 * \brief VertexArray constructor.
 *
 * This constructor initializes a VertexArray object with default values.
 */
VertexArray::VertexArray()
	: m_RendererID(0)
{
}

/*!
 * \brief VertexArray destructor.
 *
 * This destructor deletes the Vertex Array Object (VAO) when the object is destroyed.
 */
VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID)); //delete VAO when object is destroyed
}

/*!
 * \brief Set the renderer ID for the VertexArray.
 * \param rendererID The OpenGL ID for the VAO.
 *
 * This function sets the internal renderer ID for the VertexArray.
 */
void VertexArray::SetRendererID(unsigned int rendererID)
{
	m_RendererID = rendererID; //set the internal Renderer ID
}

/*!
 * \brief Generate a new OpenGL renderer ID for the VertexArray.
 *
 * This function generates a new OpenGL renderer ID (VAO ID) for the VertexArray
 * and makes it the active VAO.
 */
void VertexArray::GenerateRendererID() const
{
	GLuint rendererID;
	GLCall(glGenVertexArrays(1, &rendererID)); //new VAO ID
	const_cast<VertexArray*>(this)->SetRendererID(rendererID);
	GLCall(glBindVertexArray(m_RendererID)); //bind newly generated VAO
}

/*!
 * \brief Add a vertex buffer to the VertexArray.
 * \param vb The vertex buffer to add.
 * \param layout The layout specifying the arrangement of vertex attributes.
 *
 * This function adds a vertex buffer to the VertexArray and configures the
 * vertex attributes based on the provided layout.
 */
void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();		//bind to make VAO the active VAO
	vb.Bind();	//bind vertex buffer
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	//configure vertex attributes
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		//links buffer to VAO
		GLCall(glVertexAttribPointer(i, element.count, element.type,
			element.normalized, layout.GetStride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(offset))));
		//calculate offset for next attribute based on current element
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
	
}

/*!
 * \brief Bind the VertexArray as the active VAO.
 *
 * This function binds the VertexArray to make it the active Vertex Array Object (VAO).
 */
void VertexArray::Bind() const
{
	if (m_RendererID == 0)
	{
		GenerateRendererID(); //generate new VAO if it doesn't exist
	}
	//bind to make the new VAO active
	GLCall(glBindVertexArray(m_RendererID));
}

/*!
 * \brief Unbind the currently active VAO.
 *
 * This function unbinds the currently active Vertex Array Object (VAO).
 */
void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
