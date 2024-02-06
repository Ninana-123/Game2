

#include "pch.h"
#include "PickingFBO.h"

// Default constructor initializing member variables
PickingFBO::PickingFBO() : fbo(0), texture(0), width(0), height(0) {}

// Destructor releasing OpenGL resources
PickingFBO::~PickingFBO() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
}

// Initializes the FBO with the given width and height
void PickingFBO::Initialize(int w, int h) {
    width = w;
    height = h;
    SetupFBO();
    SetupTexture();
}

// Binds the FBO for rendering
void PickingFBO::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// Unbinds the FBO
void PickingFBO::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Returns the ID of the attached texture
GLuint PickingFBO::GetTexID() const {
    return texture;
}

// Creates and configures the OpenGL framebuffer object (FBO)
void PickingFBO::SetupFBO() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// Creates and configures the OpenGL texture attached to the FBO
void PickingFBO::SetupTexture() {
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

// Resizes the FBO and its attached texture to the new dimensions
void PickingFBO::Resize(int newWidth, int newHeight)
{
    // Delete the old texture and FBO
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &fbo);

    // Recreate the FBO and texture with the new size
    Initialize(newWidth, newHeight);
}

glm::vec3 PickingFBO::ReadPixelColor(int x, int y) 
{
    glm::vec3 color;
    glBindFramebuffer(GL_READ_FRAMEBUFFER, fbo);
    glReadPixels(x, height - y, 1, 1, GL_RGB, GL_FLOAT, &color[0]);
    glBindFramebuffer(GL_READ_FRAMEBUFFER, 0);
    return color;
}