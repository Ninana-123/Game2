#pragma once

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
    Texture(const std::string& path);
    ~Texture();

    void InitGL();  // Initialize OpenGL components
    void Bind(unsigned int slot) const;
    void Unbind() const;
};