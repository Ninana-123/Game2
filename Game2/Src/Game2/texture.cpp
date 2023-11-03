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

/*!
 * \brief Texture default constructor.
 *
 * This constructor initializes a Texture object with default values.
 */
Texture::Texture()
    : m_Filepath(""), m_RendererID(0), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0), m_RenderPosX(0.0f), m_RenderPosY(0.0f)
{
}

/*!
 * \brief Texture constructor with file path.
 * \param path The file path to the texture image.
 *
 * This constructor creates a Texture object and loads the image from the specified file path.
 */
Texture::Texture(const std::string& path)
    : m_Filepath(path), m_RendererID(0), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0), m_RenderPosX(0.0f), m_RenderPosY(0.0f)
{
    // Enable vertical flipping of loaded images
    stbi_set_flip_vertically_on_load(1);

    // Load the image data from the file using stb_image
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
}

/*!
 * \brief Texture destructor.
 *
 * This destructor releases the memory allocated for the texture image.
 */
Texture::~Texture()
{
    if (m_LocalBuffer)
    {
        stbi_image_free(m_LocalBuffer);
    }
}

/*!
 * \brief Initialize the OpenGL texture.
 *
 * This function generates and initializes an OpenGL texture using the loaded image data.
 */
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

/*!
 * \brief Bind the texture to a texture slot.
 * \param slot The texture slot to bind to.
 *
 * This function binds the texture to a specific texture slot in OpenGL.
 */
void Texture::Bind(unsigned int slot) const
{
    // Bind texture to a specific texture slot
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

/*!
 * \brief Unbind the currently bound texture.
 *
 * This function unbinds the currently bound OpenGL texture.
 */
void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

/*!
 * \brief Load texture data from the specified file path.
 *
 * This function loads the texture data from the specified file path, enabling vertical flipping of loaded images.
 *
 * \return True if the texture data is loaded successfully, false otherwise.
 */
bool Texture::Load()
{
    // Enable vertical flipping of loaded images
    stbi_set_flip_vertically_on_load(1);

    // Load the image data from data member m_Filepath
    m_LocalBuffer = stbi_load(m_Filepath.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    return m_LocalBuffer != nullptr;
}

/*!
 * \brief Load a new texture from a file.
 * \param path The file path to the new texture image.
 * \return True if the loading process was successful; false otherwise.
 *
 * This function loads a new texture image from the specified file path and updates
 * the Texture object with the new image data.
 */
bool Texture::Load(const std::string& path)
{
    // Enable vertical flipping of loaded images
    stbi_set_flip_vertically_on_load(1);

    // Load the image data from the file using stb_image
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // Update the file path
    m_Filepath = path;

    // Check if the loading process was successful
    return m_LocalBuffer != nullptr;
}

/*!
 * \brief Set the rendering position of the texture.
 * \param posX The x-coordinate of the rendering position.
 * \param posY The y-coordinate of the rendering position.
 *
 * This function sets the rendering position of the texture for rendering.
 */
void Texture::SetRenderPos(float posX, float posY)
{
    m_RenderPosX = posX;
    m_RenderPosY = posY;
}

/*!
 * \brief Set the file path for the texture.
 *
 * \param path The file path to set.
 */
void Texture::SetFilePath(const std::string& path)
{
    m_Filepath = path;
}

/*!
 * \brief update texture with new buffer
 *
 * This function updates the texture with the new loaded buffer
 */
void Texture::UpdateBufferData()
{
    // Upload image data to OpenGL texture
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    glBindTexture(GL_TEXTURE_2D, 0);

}

/*!
 * \brief Assignment operator for texture objects.
 *
 * This operator copies the data from another texture object.
 *
 * \param other The texture object to copy data from.
 * \return Reference to the modified texture object.
 */
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
