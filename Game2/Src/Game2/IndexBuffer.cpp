#include "pch.h"
#include "IndexBuffer.h"
#include "Renderer.h"

IndexBuffer::IndexBuffer()
    : m_RendererID(0), m_Data(nullptr), m_Count(0)
{
}

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_RendererID(0), m_Data(data), m_Count(count)
{
}

IndexBuffer::~IndexBuffer()
{
    if (m_RendererID != 0)
    {
        //delete openGL buffers if it exists
        GLCall(glDeleteBuffers(1, &m_RendererID));
        m_RendererID = 0;
    }
}

void IndexBuffer::GenerateBuffer() const
{
    if (m_RendererID == 0)
    {
#if !defined(NDEBUG) || defined(_DEBUG)
        static_assert(sizeof(unsigned int) == sizeof(GLuint), "Size mismatch between unsigned int and GLuint");
#endif
        GLuint rendererID;
        //store its ID in m_rendererID
        GLCall(glGenBuffers(1, &rendererID));
        const_cast<GLuint&>(m_RendererID) = rendererID;

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_Data, GL_STATIC_DRAW));
    }
}

void IndexBuffer::Bind() const
{
    GenerateBuffer();  // Ensure the buffer is generated before binding
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); //bind element array buffer
}

void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
{
    m_Data = data;
    m_Count = count;
    GenerateBuffer();  // Ensure the buffer is generated before setting data
}