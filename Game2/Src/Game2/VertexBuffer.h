/******************************************************************************/
/*!
\file		VertexBuffer.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the declaration of the VertexBuffer class, 
			which represents a vertex buffer in OpenGL.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#ifndef ENGINE_VERTEXBUFFER_H
#define ENGINE_VERTEXBUFFER_H

// Represents a vertex buffer in OpenGL, storing vertex data.
class VertexBuffer
{
private:
	//internal openGL Renderer ID (buffer)
	unsigned int m_RendererID; 
public:

	/*!
	 * \brief VertexBuffer constructor.
	 * \param data Pointer to the vertex data.
	 * \param size Size of the vertex data.
	 *
	 * This constructor generates a new OpenGL vertex buffer and stores the provided vertex data in it.
	 */
	VertexBuffer(const void* data, unsigned int size); 

	/*!
	 * \brief VertexBuffer destructor.
	 *
	 * This destructor frees up the OpenGL resources associated with the vertex buffer.
	 */
	~VertexBuffer();

	/*!
	 * \brief Set the data for the vertex buffer.
	 *
	 * This function binds the vertex buffer and sets its data with the specified data and size.
	 *
	 * \param data A pointer to the data to be copied into the buffer.
	 * \param size The size of the data in bytes.
	 */
	void SetData(const void* data, unsigned int size);

	/*!
	 * \brief Binds the vertex buffer for rendering.
	 *
	 * This function binds the vertex buffer for rendering, allowing it to be used in drawing operations.
	 */
	void Bind() const;

	/*!
	 * \brief Unbinds the vertex buffer to prevent accidental modification.
	 *
	 * This function unbinds the vertex buffer, preventing it from being accidentally modified during other OpenGL operations.
	 */
	void Unbind() const;
};
#endif ENGINE_VERTEXBUFFER_H