/******************************************************************************/
/*!
\file		Renderer.h
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
#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak(); 
#define GLCall(x) GLClearError();\
            x;\
            ASSERT(GLLogCall(#x, __FILE__, __LINE__))

//-----------functions to deal with errors in OpenGL--------------------
void GLClearError();

bool GLLogCall(const char* function, const char* file, int line);

//-----------------------------------------------------------------------

class Renderer
{
private:

public:
    void Clear() const;
    void Draw(VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;

};