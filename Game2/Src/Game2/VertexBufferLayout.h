/******************************************************************************/
/*!
\file		VertexBufferLayout.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains VertexBufferLayout class, which is used for the
			layout of vertex data in OpenGL buffers.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#include"Renderer.h"
#include <vector>
#include <GL/glew.h>
#include <stdexcept>

struct VertexBufferElement
{
	unsigned int  type;		//data type
	unsigned int  count;	//no. of elements
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
			//data types and the size of the respective types in bytes
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1; //char
		}
		ASSERT(false); //unsupported data type, debug
		return 0;
	}
};

class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;	//collection of vertex buffer elements
	unsigned int m_Stride;							//the size of vertex buffer
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	template<typename T>
	void Push(unsigned int count)
	{
		throw std::runtime_error("Unsupported data type in VertexBufferLayout::Push");
	}

	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}
	//retrieves vector of vertex buffer elements
	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }
	//retrieves stride(size) of vertex buffer
	inline unsigned int GetStride() const { return m_Stride; }
};