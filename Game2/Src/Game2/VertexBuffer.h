#pragma once

#ifndef ENGINE_VERTEXBUFFER_H
#define ENGINE_VERTEXBUFFER_H

class VertexBuffer
{
private:
	//internal openGL Renderer ID (buffer)
	unsigned int m_RendererID; 
public:
	//constructor that takes data and size as input
	VertexBuffer(const void* data, unsigned int size); 
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

};
#endif ENGINE_VERTEXBUFFER_H