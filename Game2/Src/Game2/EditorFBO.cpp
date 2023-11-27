#include "pch.h"
#include "EditorFBO.h"
#include <iostream>

EditorFBO::EditorFBO() : fbo(0), texture(0), width(0), height(0) {}

EditorFBO::~EditorFBO() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
}

void EditorFBO::Initialize(int w, int h) {
    width = w;
    height = h;
    SetupFBO();
    SetupTexture();
}

void EditorFBO::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void EditorFBO::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GLuint EditorFBO::GetTexID() const {
    return texture;
}

void EditorFBO::SetupFBO() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void EditorFBO::SetupTexture() {
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture, 0);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cerr << "ERROR::EDITORFBO:: Framebuffer is not complete!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void EditorFBO::Resize(int newWidth, int newHeight)
{
    // Delete the old texture and FBO
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &fbo);

    // Recreate the FBO and texture with the new size
    Initialize(newWidth, newHeight);
}