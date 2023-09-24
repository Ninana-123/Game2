#pragma once

#ifndef ENGINE_VERTEXARRAY_H
#define ENGINE_VERTEXARRAY_H

#include"VertexBuffer.h"

class VertexBufferLayout; //forward declaration

class VertexArray
{
private:
	unsigned int m_RendererID; //identifier for VAO
public:
	VertexArray();
	~VertexArray();

	void SetRendererID(unsigned int rendererID);
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout); //add buffer with a specific layout
	void GenerateRendererID() const; //generate a new renderer ID (VAO)
	void Bind() const; //bind the VAO for rendering
	void Unbind() const; //unbind the VAO
};
#endif ENGINE_VERTEXARRAY_H