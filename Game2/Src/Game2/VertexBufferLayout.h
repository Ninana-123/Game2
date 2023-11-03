/******************************************************************************/
/*!
\file		VertexBufferLayout.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the VertexBufferLayout class, which represents the
			layout of vertex buffer data.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
/******************************************************************************/
#pragma once
#ifndef ENGINE_VERTEXBUFFERLAYOUT_H
#define ENGINE_VERTEXBUFFERLAYOUT_H

#include"Renderer.h"
#include <GL/glew.h>
#include <vector>
#include <stdexcept>

// Represents an element within the vertex buffer layout, specifying data type, count, and normalization.
struct VertexBufferElement
{
	unsigned int  type;			//data type (eg. GL_FLOAT, GL_UNSIGNED_INT, etc)
	unsigned int  count;		//no. of elements
	unsigned char normalized;   //indicates whether data is normalized

	// Gets the size of the specified data type in bytes.
	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		//Map data types and the size of the respective types in bytes
		case GL_FLOAT:			return 4;
		case GL_UNSIGNED_INT:	return 4;
		case GL_UNSIGNED_BYTE:	return 1; //char
		}
		ASSERT(false); //unsupported data type, debug
		return 0;
	}
};

// Represents the layout of a vertex buffer, including a collection of vertex buffer elements and the buffer's stride.
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;	//collection of vertex buffer elements
	unsigned int m_Stride;							//the size of vertex buffer
public:
	VertexBufferLayout()
		: m_Stride(0) {}

	/*!
	 * \brief Adds a new element to the layout.
	 * \tparam T Data type of the element.
	 * \param count Number of elements.
	 * \throw std::runtime_error if the data type is unsupported.
	 */
	template<typename T>
	void Push(unsigned int count)
	{
		throw std::runtime_error("Unsupported data type in VertexBufferLayout::Push");
	}

	/*!
	 * \brief Adds float data to the layout.
	 * \param count Number of float elements.
	 */
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	/*!
	 * \brief Adds unsigned int data to the layout.
	 * \param count Number of unsigned int elements.
	 */
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	/*!
	 * \brief Adds unsigned int data to the layout.
	 * \param count Number of unsigned int elements.
	 */
	template<>
	void Push<unsigned char>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	/*!
	 * \brief Retrieves the vector of vertex buffer elements.
	 * \return Vector of vertex buffer elements.
	 */
	inline const std::vector<VertexBufferElement> GetElements() const& { return m_Elements; }

	/*!
	 * \brief Retrieves the stride (size) of the vertex buffer.
	 * \return Size of the vertex buffer.
	 */
	inline unsigned int GetStride() const { return m_Stride; }
};
#endif ENGINE_VERTEXBUFFERLAYOUT_H