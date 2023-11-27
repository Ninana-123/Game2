/******************************************************************************/
/*!
\file		EditorFBO.h
\author 	Liu Xujie
\par    	email: l.xujie@digipen.edu
\date   	27/11/2023
\brief		This file contains the implementation of the EditorFBO.

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef EDITOR_FBO_H
#define EDITOR_FBO_H

#include <GL/glew.h>

/**
 * @brief Represents an OpenGL Framebuffer Object (FBO) used in the editor for off-screen rendering.
 */
class EditorFBO {
public:
    /**
     * @brief Default constructor initializing member variables.
     */
    EditorFBO();

    /**
     * @brief Destructor releasing OpenGL resources.
     */
    ~EditorFBO();

    /**
    * @brief Initializes the FBO with the given width and height.
    * @param width The width of the FBO.
    * @param height The height of the FBO.
    */
    void Initialize(int width, int height);

    /**
    * @brief Binds the FBO for rendering.
    */
    void Bind();

    /**
     * @brief Unbinds the FBO.
     */
    void Unbind();

    /**
    * @brief Gets the ID of the attached texture.
    * @return The OpenGL texture ID.
    */
    GLuint GetTexID() const;

    /**
     * @brief Resizes the FBO and its attached texture to the new dimensions.
     * @param newWidth The new width of the FBO.
     * @param newHeight The new height of the FBO.
     */
    void Resize(int newWidth, int newHeight);
   

private:
    GLuint fbo;
    GLuint texture;
    int width, height;

    /**
     * @brief Creates and configures the OpenGL framebuffer object (FBO).
     */
    void SetupFBO();

    /**
    * @brief Creates and configures the OpenGL texture attached to the FBO.
    */
    void SetupTexture();
};

#endif // EDITOR_FBO_H
