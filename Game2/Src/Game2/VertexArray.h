/******************************************************************************/
/*!
\file		VertexArray.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the declaration of the VertexArray class, which
			represents a Vertex Array Object which is used to efficiently organize
			and manage vertex data for rendering 3D object.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include"VertexBuffer.h"

class VertexBufferLayout; //forward declaration

class VertexArray
{
private:
	unsigned int m_RendererID; //identifier for vao
public:
	VertexArray();
	~VertexArray();

	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);

	void Bind() const;
	void Unbind() const;

};