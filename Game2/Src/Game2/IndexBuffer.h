/******************************************************************************/
/*!
\file		IndexBuffer.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

class IndexBuffer
{
private:
	unsigned int m_RendererID; //internal render id
	unsigned int m_Count;
public:
	IndexBuffer() // Default constructor
		: m_RendererID(0), m_Count(0) {}

	IndexBuffer(const unsigned int* data, unsigned int count);
	~IndexBuffer();


	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return m_Count; }
};