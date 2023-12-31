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

VertexArray::VertexArray()
	: m_RendererID(0), m_RendererBuffers(3)
{
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID)); //delete VAO when object is destroyed
}

void VertexArray::SetRendererID(unsigned int rendererID)
{
	m_RendererID = rendererID; //set the internal Renderer ID
}

void VertexArray::GenerateRendererID() const
{
	GLuint rendererID;
	GLCall(glGenVertexArrays(1, &rendererID)); //new VAO ID
	const_cast<VertexArray*>(this)->SetRendererID(rendererID);
	GLCall(glBindVertexArray(m_RendererID)); //bind newly generated VAO
}

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

void VertexArray::UpdateBuffer(unsigned int index, const void* data, size_t size)
{
	if (index < m_RendererBuffers.size()) {
		Bind(); // Bind the VAO to make it active
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererBuffers[index]); // Bind the specific buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, data); // Update the buffer data
	}
	else {
		std::cerr << "Error: Invalid buffer index " << index << std::endl;
	}
}

void VertexArray::Bind() const
{
	if (m_RendererID == 0)
	{
		GenerateRendererID(); //generate new VAO if it doesn't exist
	}
	//bind to make the new VAO active
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}
