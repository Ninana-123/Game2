/******************************************************************************/
/*!
\file		IndexBuffer.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
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
        GLCall(glDeleteBuffers(1, &m_RendererID));
        m_RendererID = 0;
    }
}

void IndexBuffer::GenerateBuffer() const
{
    if (m_RendererID == 0)
    {
        ASSERT(sizeof(unsigned int) == sizeof(GLuint));

        GLuint rendererID;
        GLCall(glGenBuffers(1, &rendererID));
        const_cast<GLuint&>(m_RendererID) = rendererID;

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_Data, GL_STATIC_DRAW));
    }
}



void IndexBuffer::Bind() const
{
    GenerateBuffer();  // Ensure the buffer is generated before binding
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
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