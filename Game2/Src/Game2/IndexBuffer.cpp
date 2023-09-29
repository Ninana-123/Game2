/******************************************************************************/
/*!
\file		Renderer.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the IndexBuffer class, which
            represents an OpenGL index buffer used for rendering.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "IndexBuffer.h"
#include "Renderer.h"

/*!
 * \brief IndexBuffer default constructor.
 *
 * This constructor initializes the IndexBuffer object with default values.
 */
IndexBuffer::IndexBuffer()
    : m_RendererID(0), m_Data(nullptr), m_Count(0)
{
}

/*!
 * \brief IndexBuffer constructor with data and count.
 * \param data Pointer to the index data.
 * \param count Number of indices in the buffer.
 *
 * This constructor initializes the IndexBuffer object with provided index data and count.
 */
IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
    : m_RendererID(0), m_Data(data), m_Count(count)
{
}

/*!
 * \brief IndexBuffer destructor.
 *
 * This destructor cleans up the OpenGL buffer resources when the IndexBuffer object is destroyed.
 */
IndexBuffer::~IndexBuffer()
{
    if (m_RendererID != 0)
    {
        // Delete OpenGL buffers if they exist
        GLCall(glDeleteBuffers(1, &m_RendererID));
        m_RendererID = 0;
    }
}

/*!
 * \brief Generate the OpenGL buffer.
 *
 * This function generates the OpenGL index buffer and uploads the index data to it.
 * It should be called before any binding or rendering with the buffer.
 */
void IndexBuffer::GenerateBuffer() const
{
    if (m_RendererID == 0)
    {
#if !defined(NDEBUG) || defined(_DEBUG)
        static_assert(sizeof(unsigned int) == sizeof(GLuint), "Size mismatch between unsigned int and GLuint");
#endif
        GLuint rendererID;
        // Store its ID in m_rendererID
        GLCall(glGenBuffers(1, &rendererID));
        const_cast<GLuint&>(m_RendererID) = rendererID;

        GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
        GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Count * sizeof(unsigned int), m_Data, GL_STATIC_DRAW));
    }
}

/*!
 * \brief Bind the index buffer for rendering.
 *
 * This function binds the OpenGL index buffer for rendering. It ensures the buffer is generated
 * before binding.
 */
void IndexBuffer::Bind() const
{
    GenerateBuffer();  // Ensure the buffer is generated before binding
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // Bind the element array buffer
}

/*!
 * \brief Unbind the currently bound index buffer.
 *
 * This function unbinds the currently bound OpenGL index buffer.
 */
void IndexBuffer::Unbind() const
{
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

/*!
 * \brief Set new index data and count for the buffer.
 * \param data Pointer to the new index data.
 * \param count Number of new indices in the buffer.
 *
 * This function updates the IndexBuffer with new index data and count.
 * It ensures the buffer is generated before setting the data.
 */
void IndexBuffer::SetData(const unsigned int* data, unsigned int count)
{
    m_Data = data;
    m_Count = count;
    GenerateBuffer();  // Ensure the buffer is generated before setting data
}
