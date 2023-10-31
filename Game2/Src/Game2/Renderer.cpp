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

/*!
 * \brief Clear the OpenGL color buffer.
 *
 * This function clears the OpenGL color buffer, preparing it for rendering.
 */
void GLClearError()
{
    while (glGetError()); // Clear OpenGL errors
}

/*!
 * \brief Check and log OpenGL errors.
 * \param function The name of the function where the error check occurs.
 * \param file The name of the source file where the error check occurs.
 * \param line The line number where the error check occurs.
 * \return True if there are no OpenGL errors; false otherwise.
 *
 * This function checks for OpenGL errors and logs them along with the function name,
 * source file, and line number where the error occurred. It returns true if there
 * are no errors, and false otherwise.
 */
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

/*!
 * \brief Clear the OpenGL color buffer.
 *
 * This function clears the OpenGL color buffer, preparing it for rendering.
 */
void Renderer::Clear() const
{
    // Render here
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

/*!
 * \brief Draw using a VertexArray, IndexBuffer, and Shader.
 * \param va The VertexArray to use for drawing.
 * \param ib The IndexBuffer specifying the vertices to draw.
 * \param shader The Shader program to use for rendering.
 *
 * This function binds the VertexArray, IndexBuffer, and Shader, and then
 * draws the specified elements in one call using OpenGL.
 */
void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    // Draw elements together in one call
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}