#include "pch.h"
#include "VertexBuffer.h"
#include "Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    //generate a new buffer and store its ID in m_RendererID
    GLCall(glGenBuffers(1, &m_RendererID));
    //bind the newly created buffer as an array buffer
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
    //stores the vertex data the buffer data
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::~VertexBuffer()
{
    //free up resources
    GLCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const
{
    //bind vertex buffer for rendering
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID));
}

void VertexBuffer::Unbind() const
{
    //unbind vertex buffer to prevent accidental modification
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}