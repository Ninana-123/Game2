/******************************************************************************/
/*!
\file		VertexArray.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the VertexArray class. It
			provides functions for managing Vertex Array Objects (VAOs), adding
			vertex buffers, and setting vertex buffer layouts.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_VERTEXARRAY_H
#define ENGINE_VERTEXARRAY_H

#include"VertexBuffer.h"

class VertexBufferLayout; //forward declaration

class VertexArray
{
private:
	unsigned int m_RendererID; //identifier for VAO
	std::vector<unsigned int> m_RendererBuffers; // OpenGL IDs for vertex buffers
public:
	/*!
	 * \brief VertexArray constructor.
	 *
	 * This constructor initializes a VertexArray object with default values.
	 */
	VertexArray();

	/*!
	 * \brief VertexArray destructor.
	 *
	 * This destructor deletes the Vertex Array Object (VAO) when the object is destroyed.
	 */
	~VertexArray();

	/*!
	 * \brief Set the renderer ID for the VertexArray.
	 * \param rendererID The OpenGL ID for the VAO.
	 *
	 * This function sets the internal renderer ID for the VertexArray.
	 */
	void SetRendererID(unsigned int rendererID);

	/*!
	 * \brief Add a vertex buffer to the VertexArray.
	 * \param vb The vertex buffer to add.
	 * \param layout The layout specifying the arrangement of vertex attributes.
	 *
	 * This function adds a vertex buffer to the VertexArray and configures the
	 * vertex attributes based on the provided layout.
	 */
	void AddBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout); //add buffer with a specific layout

	/*!
	 * \brief Update the buffer data in the vertex array.
	 *
	 * This function updates the data of a specific buffer in the vertex array.
	 *
	 * \param index The index of the buffer to be updated.
	 * \param data A pointer to the new data to be copied into the buffer.
	 * \param size The size of the data in bytes.
	 */
	void UpdateBuffer(unsigned int index, const void* data, size_t size);

	/*!
	 * \brief Generate a new OpenGL renderer ID for the VertexArray.
	 *
	 * This function generates a new OpenGL renderer ID (VAO ID) for the VertexArray
	 * and makes it the active VAO.
	 */
	void GenerateRendererID() const; //generate a new renderer ID (VAO)

	/*!
	 * \brief Bind the VertexArray as the active VAO.
	 *
	 * This function binds the VertexArray to make it the active Vertex Array Object (VAO).
	 */
	void Bind() const; //bind the VAO for rendering

	/*!
	 * \brief Unbind the currently active VAO.
	 *
	 * This function unbinds the currently active Vertex Array Object (VAO).
	 */
	void Unbind() const; //unbind the VAO
};
#endif ENGINE_VERTEXARRAY_H