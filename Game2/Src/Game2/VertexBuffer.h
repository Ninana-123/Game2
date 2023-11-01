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
	 * \brief Constructor for VertexBuffer.
	 * \param data Pointer to the vertex data.
	 * \param size Size of the vertex data.
	 */
	VertexBuffer(const void* data, unsigned int size); 

	// Destructor for VertexBuffer.
	~VertexBuffer();

	// Binds the vertex buffer.
	void Bind() const;

	// Unbinds the vertex buffer.
	void Unbind() const;

	void SetData(const void* data, unsigned int size);
};
#endif ENGINE_VERTEXBUFFER_H