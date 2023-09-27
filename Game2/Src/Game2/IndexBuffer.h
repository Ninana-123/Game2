#pragma once

#ifndef ENGINE_INDEXBUFFER_H
#define ENGINE_INDEXBUFFER_H

class IndexBuffer
{
private:
	unsigned int m_RendererID; //internal Render ID for index buffer
	unsigned int m_Count;		//no. of indices in buffer
	const unsigned int* m_Data; //pointer to index data
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void SetData(const unsigned int* data, unsigned int count); //set index data
	void GenerateBuffer() const; //generate openGL buffer
	void Bind() const; //bind index buffer
	void Unbind() const; //unbind index buffer
	inline unsigned int GetCount() const { return m_Count; } //get no. of indices
};
#endif ENGINE_INDEXBUFFER_H