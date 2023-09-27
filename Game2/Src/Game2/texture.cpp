
#include "pch.h"
#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture()
    : m_Filepath(""), m_RendererID(0), m_LocalBuffer(nullptr),
    m_Width(0), m_Height(0), m_BPP(0), m_RenderPosX(0.0f), m_RenderPosY(0.0f)
{
}

//create a texture object and and initializing it with texture file
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
    // Bind texture to a specific texture slot
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}

//change the texture of an existing texture object by loading a different image file
void Texture::Load(const std::string& path)
{
    // Enable vertical flipping of loaded images
    stbi_set_flip_vertically_on_load(1);

    // Load the image data from the file using stb_image
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);

    // Update the file path
    m_Filepath = path;
}

void Texture::SetRenderPos(float posX, float posY)
{
    m_RenderPosX = posX;
    m_RenderPosY = posY;
}