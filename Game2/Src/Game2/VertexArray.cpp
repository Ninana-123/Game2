/******************************************************************************/
/*!
\file		VertexArray.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the VertexArray class. It 
			provides functions for managing VAOs, adding vertex buffers, and
            setting vertex buffer layouts.

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
{
	//generate vao and store its ID
	GLCall(glGenVertexArrays(1, &m_RendererID));

}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout)
{
	Bind();		//bind to make vao the active vao
	vb.Bind();	//bind vertex buffer
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	//configure vertex attributes
	for (unsigned int i = 0; i < elements.size(); i++)
	{
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
		//links buffer to vao
		GLCall(glVertexAttribPointer(i, element.count, element.type, 
			element.normalized, layout.GetStride(), reinterpret_cast<const GLvoid*>(static_cast<uintptr_t>(offset))));
		//calculate offset for next attribute based on current element
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}