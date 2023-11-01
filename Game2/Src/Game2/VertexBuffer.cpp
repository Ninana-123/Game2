/******************************************************************************/
/*!
\file		VertexBuffer.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the VertexBuffer class functions, 
            which manage OpenGL vertex buffers.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer.h"

/*!
 * \brief VertexBuffer constructor.
 * \param data Pointer to the vertex data.
 * \param size Size of the vertex data.
 *
 * This constructor generates a new OpenGL vertex buffer and stores the provided vertex data in it.
 */
VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //generate a new buffer and store its ID in m_RendererID
    GLCall(glGenBuffers(1, &m_RendererID));
    //bind the newly created buffer as an array buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    //stores the vertex data the buffer data
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW));
}

/*!
 * \brief VertexBuffer destructor.
 *
 * This destructor frees up the OpenGL resources associated with the vertex buffer.
 */
VertexBuffer::~VertexBuffer()
{
    //free up resources
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

/*!
 * \brief Binds the vertex buffer for rendering.
 *
 * This function binds the vertex buffer for rendering, allowing it to be used in drawing operations.
 */
void VertexBuffer::Bind() const
{
    //bind vertex buffer for rendering
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

/*!
 * \brief Unbinds the vertex buffer to prevent accidental modification.
 *
 * This function unbinds the vertex buffer, preventing it from being accidentally modified during other OpenGL operations.
 */
void VertexBuffer::Unbind() const
{
    //unbind vertex buffer to prevent accidental modification
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}

void VertexBuffer::SetData(const void* data, unsigned int size)
{
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}