
#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID; //internal render id
	unsigned int m_Count;
	const unsigned int* m_Data;
public:
	IndexBuffer();
	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();
	void SetData(const unsigned int* data, unsigned int count);
	void GenerateBuffer() const;
	void Bind() const;
	void Unbind() const;
	inline unsigned int GetCount() const { return m_Count; }
};