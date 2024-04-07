/******************************************************************************/
/*!
\file		Renderer.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the Renderer class, which
            provides functions for OpenGL rendering.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "Renderer.h"
#include <iostream>
#include <GLFW/glfw3.h>

void GLClearError()
{
    while (glGetError()); // Clear OpenGL errors
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "):" << function << " " <<
            file << ":" << line << std::endl;
        return false; // GL call was not successful
    }
    return true;
}

void Renderer::Clear() const
{
    // Render here
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    // Check if the window is minimized
    if (!glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_ICONIFIED))
    {
        // Window is not minimized, proceed with rendering
        shader.Bind();
        va.Bind();
        ib.Bind();
        // Draw elements together in one call
        GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
    }
    else
    {
        // Window is minimized, do not perform rendering operations
        std::cout << "Window is minimized, skipping rendering." << std::endl;
    }
}