/******************************************************************************/
/*!
\file		Texture.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the Texture class, which
            represents an OpenGL texture and handles texture loading and rendering.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include <GLFW/glfw3.h>

Texture::Texture()
    : m_Filepath(""), m_RendererID(0), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0), m_RenderPosX(0.0f), m_RenderPosY(0.0f)
{
}

Texture::Texture(const std::string& path)
    : m_Filepath(path), m_RendererID(0), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0), m_RenderPosX(0.0f), m_RenderPosY(0.0f)
{
    // Enable vertical flipping of loaded images
    stbi_set_flip_vertically_on_load(1);

    // Load the image data from the file using stb_image
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
}

Texture::~Texture()
{
    if (m_LocalBuffer)
    {
        stbi_image_free(m_LocalBuffer);
    }
}

void Texture::InitGL()
{
    // Generate a new OpenGL texture
    glGenTextures(1, &m_RendererID);
    glBindTexture(GL_TEXTURE_2D, m_RendererID);

    // Set texture parameters (filtering and wrapping)
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

    // Upload image data to OpenGL texture
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::Bind(unsigned int slot) const
{
    // Check if the window is minimized
    if (!glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_ICONIFIED))
    {
        // Window is not minimized, proceed with binding the texture
        GLCall(glActiveTexture(GL_TEXTURE0 + slot));
        GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
    }
    else
    {
        // Window is minimized, do not perform texture binding
        std::cout << "Window is minimized, skipping texture binding." << std::endl;
    }
}

void Texture::Unbind() const
{
    if (!glfwGetWindowAttrib(glfwGetCurrentContext(), GLFW_ICONIFIED)) 
    {
        GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }
    else
    {
        std::cout << "Window is minimized, skipping texture binding." << std::endl;
    }
}

bool Texture::Load()
{
    // Enable vertical flipping of loaded images
    stbi_set_flip_vertically_on_load(1);

    // Load the image data from data member m_Filepath
    m_LocalBuffer = stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    return m_LocalBuffer != nullptr;
}

void Texture::LoadNewTexture(const std::string& newPath) {
    // Load the new image data
    stbi_set_flip_vertically_on_load(1);
    unsigned char* newLocalBuffer = stbi_load(newPath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // Check if loading was successful
    if (newLocalBuffer) {
        // Delete the old OpenGL texture
        glDeleteTextures(1, &m_RendererID);

        // Generate a new OpenGL texture
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Set texture parameters
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        // Upload the new image data to OpenGL texture
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, newLocalBuffer));
        glBindTexture(GL_TEXTURE_2D, 0);

        // Free the old local buffer
        stbi_image_free(m_LocalBuffer);

        // Set the new local buffer
        m_LocalBuffer = newLocalBuffer;

        // Update file path
        m_Filepath = newPath;

        std::cout << "Updated FilePath: " << m_Filepath << std::endl;
        std::cout << "Target ID: " << m_RendererID << std::endl;
    }
    else {
        // Handle the case where loading fails
        std::cerr << "Failed to load the new texture." << std::endl;
    }
}

void Texture::UpdateTexture(const std::string& newPath)
{
    // Load the new image data
    stbi_set_flip_vertically_on_load(1);
    unsigned char* newLocalBuffer = stbi_load(newPath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // Check if loading was successful
    if (newLocalBuffer) {
        // Delete the old OpenGL texture
        glDeleteTextures(1, &m_RendererID);

        // Generate a new OpenGL texture
        glGenTextures(1, &m_RendererID);
        glBindTexture(GL_TEXTURE_2D, m_RendererID);

        // Set texture parameters
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
        GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

        // Upload the new image data to OpenGL texture
        GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, newLocalBuffer));
        glBindTexture(GL_TEXTURE_2D, 0);

        // Free the old local buffer
        stbi_image_free(m_LocalBuffer);

        // Set the new local buffer
        m_LocalBuffer = newLocalBuffer;

        // Update file path
        m_Filepath = newPath;

        std::cout << "Updated FilePath: " << m_Filepath << std::endl;
        std::cout << "New Target ID: " << m_RendererID << std::endl;
    }
    else {
        // Handle the case where loading fails
        std::cerr << "Failed to load the new texture." << std::endl;
    }
}

void Texture::SetRenderPos(float posX, float posY)
{
    m_RenderPosX = posX;
    m_RenderPosY = posY;
}

void Texture::SetFilePath(const std::string& path)
{
    m_Filepath = path;
}

void Texture::UpdateBufferData()
{
    // Upload image data to OpenGL texture
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    glBindTexture(GL_TEXTURE_2D, 0);

}

Texture& Texture::operator=(const Texture& other)
{
    if (this != &other) {
        // Check if the other texture has valid data
        if (other.m_LocalBuffer != nullptr) {
            // Free existing local buffer
            if (m_LocalBuffer) {
                stbi_image_free(m_LocalBuffer);
            }

            // Copy other's data
            m_Filepath = other.m_Filepath;
            m_Width = other.m_Width;
            m_Height = other.m_Height;
            m_BPP = other.m_BPP;
            m_RenderPosX = other.m_RenderPosX;
            m_RenderPosY = other.m_RenderPosY;

            // Allocate and copy local buffer
            m_LocalBuffer = stbi_load(other.m_Filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);
        }
        else {
            // If other's local buffer is nullptr, set local buffer to nullptr as well
            m_LocalBuffer = nullptr;
        }
    }

    return *this;
}
