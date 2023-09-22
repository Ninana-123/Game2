
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

	void SetRendererID(unsigned int rendererID);
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout);
	void GenerateRendererID() const;
	void Bind() const;
	void Unbind() const;

};