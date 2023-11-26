/******************************************************************************/
/*!
\file		VertexArray.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the VertexArray class. It
			provides functions for managing Vertex Array Objects (VAOs), adding
			vertex buffers, and setting vertex buffer layouts.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#ifndef ENGINE_VERTEXARRAY_H
#define ENGINE_VERTEXARRAY_H

#include"VertexBuffer.h"

class VertexBufferLayout; //forward declaration

class VertexArray
{
private:
	unsigned int m_RendererID; //identifier for VAO
	std::vector<unsigned int> m_RendererBuffers; // OpenGL IDs for vertex buffers
public:
	VertexArray();
	~VertexArray();

	void SetRendererID(unsigned int rendererID);
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout); //add buffer with a specific layout
	void UpdateBuffer(unsigned int index, const void* data, size_t size);
	void GenerateRendererID() const; //generate a new renderer ID (VAO)
	void Bind() const; //bind the VAO for rendering
	void Unbind() const; //unbind the VAO
};
#endif ENGINE_VERTEXARRAY_H