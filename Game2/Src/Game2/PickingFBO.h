#pragma once




#ifndef ENGINE_PICKING_TEXTURE_H
#define ENGINE_PICKING_TEXTURE_H

#include <GL/glew.h>
#include <glm/glm.hpp>

/**
 * @brief Represents an OpenGL Framebuffer Object (FBO) used in the editor for texture picking.
 */
class PickingFBO {
public:
    /**
     * @brief Default constructor initializing member variables.
     */
    PickingFBO();

    /**
     * @brief Destructor releasing OpenGL resources.
     */
    ~PickingFBO();

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

    glm::vec3 ReadPixelColor(int x, int y);

    inline int GetWidth() { return width; }
    inline int GetHeight() { return height; }
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

#endif ENGINE_EDITOR_FBO_H
