/******************************************************************************/
/*!
\file		EditorFBO.cpp
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	27/11/2023
\brief		This file contains the implementation of the EditorFBO.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "EditorFBO.h"

// Default constructor initializing member variables
EditorFBO::EditorFBO() : fbo(0), texture(0), width(0), height(0) {}

// Destructor releasing OpenGL resources
EditorFBO::~EditorFBO() {
    glDeleteFramebuffers(1, &fbo);
    glDeleteTextures(1, &texture);
}

// Initializes the FBO with the given width and height
void EditorFBO::Initialize(int w, int h) {
    width = w;
    height = h;
    SetupFBO();
    SetupTexture();
}

// Binds the FBO for rendering
void EditorFBO::Bind() {
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// Unbinds the FBO
void EditorFBO::Unbind() {
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

// Returns the ID of the attached texture
GLuint EditorFBO::GetTexID() const {
    return texture;
}

// Creates and configures the OpenGL framebuffer object (FBO)
void EditorFBO::SetupFBO() {
    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

// Creates and configures the OpenGL texture attached to the FBO
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

// Resizes the FBO and its attached texture to the new dimensions
void EditorFBO::Resize(int newWidth, int newHeight)
{
    // Delete the old texture and FBO
    glDeleteTextures(1, &texture);
    glDeleteFramebuffers(1, &fbo);

    // Recreate the FBO and texture with the new size
    Initialize(newWidth, newHeight);
}