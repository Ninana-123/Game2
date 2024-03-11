/******************************************************************************/
/*!
\file		Texture.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the Texture class, which
            represents an OpenGL texture and handles texture loading and rendering.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include "Renderer.h"
#include <string>

struct SubTextureData {
    int width;
    int height;
    int bpp;
    unsigned char* localBuffer;
};

class Texture
{
private:
    std::string m_Filepath;
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    /*!
     * \brief Texture default constructor.
     *
     * This constructor initializes a Texture object with default values.
     */
    Texture(); // Default constructor

    /*!
     * \brief Texture constructor with file path.
     * \param path The file path to the texture image.
     *
     * This constructor creates a Texture object and loads the image from the specified file path.
     */
    Texture(const std::string& path);

    /*!
     * \brief Texture destructor.
     *
     * This destructor releases the memory allocated for the texture image.
     */
    ~Texture();

    /*!
     * \brief Initialize the OpenGL texture.
     *
     * This function generates and initializes an OpenGL texture using the loaded image data.
     */
    void InitGL();  // Initialize OpenGL components

    /*!
     * \brief Bind the texture to a texture slot.
     * \param slot The texture slot to bind to.
     *
     * This function binds the texture to a specific texture slot in OpenGL.
     */
    void Bind(unsigned int slot) const;

    /*!
     * \brief Unbind the currently bound texture.
     *
     * This function unbinds the currently bound OpenGL texture.
     */
    void Unbind() const;

    /*!
     * \brief Load texture data from the specified file path.
     *
     * This function loads the texture data from the specified file path, enabling vertical flipping of loaded images.
     *
     * \return True if the texture data is loaded successfully, false otherwise.
     */
    bool Load(); // Load texture from member path

    /*!
     * \brief Load a new texture from a file.
     * \param path The file path to the new texture image.
     * \return True if the loading process was successful; false otherwise.
     *
     * This function loads a new texture image from the specified file path and updates
     * the Texture object with the new image data.
     */
    void LoadNewTexture(const std::string& path); // Load texture from file

    void UpdateTexture(const std::string& newPath);


    /*!
     * \brief Set the rendering position of the texture.
     * \param posX The x-coordinate of the rendering position.
     * \param posY The y-coordinate of the rendering position.
     *
     * This function sets the rendering position of the texture for rendering.
     */
    void SetRenderPos(float posX, float posY); // Set rendering position

    /*!
     * \brief Get the texture ID.
     *
     * \return unsigned int
     * The OpenGL ID of the texture.
     */
    unsigned int GetTextureID() const {
        return m_RendererID;
    }

    void SetID(int id)
    {
        m_RendererID = id;
    }

    /*!
     * \brief Set the file path for the texture.
     *
     * \param path The file path to set.
     */
    void SetFilePath(const std::string& path);

    /*!
     * \brief update texture with new buffer
     *
     * This function updates the texture with the new loaded buffer
     */
    void UpdateBufferData();

    /*!
     * \brief Assignment operator for texture objects.
     *
     * This operator copies the data from another texture object.
     *
     * \param other The texture object to copy data from.
     * \return Reference to the modified texture object.
     */
    Texture& operator=(const Texture& other);

    /*!
    * \brief Get the width of the texture.
    *
    * \return int
    * The width of the texture in pixels.
    */
    inline int GetWidth() {
        return m_Width;
    }

    /*!
    * \brief Get the height of the texture.
    *
    * \return int
    * The height of the texture in pixels.
    */
    inline int GetHeight() {
        return m_Height;
    }
    
private:
    float m_RenderPosX, m_RenderPosY; // Position for rendering
};
#endif ENGINE_TEXTURE_H