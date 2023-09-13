/******************************************************************************/
/*!
\file		VertexBuffer.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the declaration of VertexBuffer Class, which
			represents a Vertex Buffer Object that stores data that can be used
			for rendering 3D object.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

class VertexBuffer
{
private:
	unsigned int m_RendererID; //internal render id
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};