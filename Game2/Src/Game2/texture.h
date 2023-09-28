

#pragma once

#ifndef ENGINE_TEXTURE_H
#define ENGINE_TEXTURE_H

#include "Renderer.h"
#include <string>

class Texture
{
private:
    std::string m_Filepath;
    unsigned int m_RendererID;
    unsigned char* m_LocalBuffer;
    int m_Width, m_Height, m_BPP;

public:
    Texture(); // Default constructor
    Texture(const std::string& path);
    ~Texture();

    void InitGL();  // Initialize OpenGL components
    void Bind(unsigned int slot) const;
    void Unbind() const;
    bool Load(const std::string& path); // Load texture from file
    void SetRenderPos(float posX, float posY); // Set rendering position

private:
    float m_RenderPosX, m_RenderPosY; // Position for rendering

};
#endif ENGINE_TEXTURE_H