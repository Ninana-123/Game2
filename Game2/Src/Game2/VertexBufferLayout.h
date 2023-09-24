#pragma once
#ifndef ENGINE_VERTEXBUFFERLAYOUT_H
#define ENGINE_VERTEXBUFFERLAYOUT_H

#include"Renderer.h"
#include <vector>
#include <GL/glew.h>
#include <stdexcept>

struct VertexBufferElement
{
	unsigned int  type;			//data type (eg. GL_FLOAT, GL_UNSIGNED_INT, etc)
	unsigned int  count;		//no. of elements
	unsigned char normalized;   //indicates whether data is normalized

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type)
		{
		//map data types and the size of the respective types in bytes
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

	//template to add new element to the layout	
	template<typename T>
	void Push(unsigned int count)
	{
		throw std::runtime_error("Unsupported data type in VertexBufferLayout::Push");
	}

	//template for adding float data to layout
	template<>
	void Push<float>(unsigned int count)
	{
		m_Elements.push_back({ GL_FLOAT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	}

	//template for adding unsigned int data to layout
	template<>
	void Push<unsigned int>(unsigned int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	//template for adding unsigned char data to layout
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
#endif ENGINE_VERTEXBUFFERLAYOUT_H