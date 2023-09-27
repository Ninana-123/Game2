
#include"pch.h"
#include "Renderer.h"
#include <iostream>

void GLClearError()
{
    while (glGetError()); //clear openGL errors
}

bool GLLogCall(const char* function, const char* file, int line)
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << "):" << function << " " <<
            file << ":" << line << std::endl;
        return false; //GL call was not successful
    }
    return true;
}

void Renderer::Clear() const
{
    //render here
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
    shader.Bind();
    va.Bind();
    ib.Bind();
    //drawn together in 1 call
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}