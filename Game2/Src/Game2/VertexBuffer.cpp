/******************************************************************************/
/*!
\file		VertexBuffer.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //generate a new buffer and store it in its ID in m_RendererID
    GLCall(glGenBuffers(1, &m_RendererID));
    //binding the newly created buffer as an array buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    //stores the position into the buffer data
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    //bind vertex buffer for rendering
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));

}

//unbind to prevent accidental modification
void VertexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));

}