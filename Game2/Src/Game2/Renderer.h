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

#ifndef ENGINE_RENDERER_H
#define ENGINE_RENDERER_H

#include <GL/glew.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) if(!(x)) __debugbreak(); //custom assertion macro
#define GLCall(x) GLClearError();\
            x;\
            ASSERT(GLLogCall(#x, __FILE__, __LINE__)) //custom openGL error handling macro

//-----------functions to deal with errors in OpenGL--------------------
void GLClearError(); //clear openGL errors

bool GLLogCall(const char* function, const char* file, int line); //log openGL errors

//-----------------------------------------------------------------------

class Renderer
{
private:

public:
    void Clear() const; //clear render buffer
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const; //draw function for rendering
};
#endif ENGINE_RENDERER_H