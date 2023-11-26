/******************************************************************************/
/*!
\file		IndexBuffer.cpp
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

	/*!
	* \brief IndexBuffer default constructor.
	*
	* This constructor initializes the IndexBuffer object with default values.
	*/
	IndexBuffer();

	/*!
	 * \brief IndexBuffer constructor with data and count.
	 * \param data Pointer to the index data.
	 * \param count Number of indices in the buffer.
	 *
	 * This constructor initializes the IndexBuffer object with provided index data and count.
	 */
	IndexBuffer(const unsigned int* data, unsigned int count);

	/*!
	* \brief IndexBuffer destructor.
	*
	* This destructor cleans up the OpenGL buffer resources when the IndexBuffer object is destroyed.
	*/
	~IndexBuffer();

	/*!
	 * \brief Set new index data and count for the buffer.
	 * \param data Pointer to the new index data.
	 * \param count Number of new indices in the buffer.
	 *
	 * This function updates the IndexBuffer with new index data and count.
	 * It ensures the buffer is generated before setting the data.
	 */
	void SetData(const unsigned int* data, unsigned int count); //set index data

	/*!
	 * \brief Generate the OpenGL buffer.
	 *
	 * This function generates the OpenGL index buffer and uploads the index data to it.
	 * It should be called before any binding or rendering with the buffer.
	 */
	void GenerateBuffer() const; //generate openGL buffer

	/*!
	 * \brief Bind the index buffer for rendering.
	 *
	 * This function binds the OpenGL index buffer for rendering. It ensures the buffer is generated
	 * before binding.
	 */
	void Bind() const; //bind index buffer

	/*!
	 * \brief Unbind the currently bound index buffer.
	 *
	 * This function unbinds the currently bound OpenGL index buffer.
	 */
	void Unbind() const; //unbind index buffer

	inline unsigned int GetCount() const { return m_Count; } //get no. of indices
};
#endif ENGINE_INDEXBUFFER_H