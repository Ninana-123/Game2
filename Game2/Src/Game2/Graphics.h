#pragma once

#ifndef ENGINE_GRAPHICS_H
#define ENGINE_GRAPHICS_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "glm/gtc/matrix_transform.hpp"

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "System.h"
#include "Component.h"
#include "Entity.h"

namespace Engine
{

    class Graphics : public System
    {
    public:
        Graphics();
        ~Graphics();

        void Initialize();
        void Update(Entity* entity) override;
        void InitializeGLEW();
        void UpdateViewport(int width, int height);
        void UpdateTransformations(int key);

        GLFWwindow* Window{};
        Shader shader;

        IndexBuffer ib;
        Renderer renderer;
        VertexArray va;
        glm::mat4 proj{};
        glm::mat4 view{};
        Texture luffyTexture;
        Texture zoroTexture;
        float vtx_postions[16]{};
        unsigned int indices[6]{};


        double programStartTime = glfwGetTime();

        bool renderTexturedSquare = false;
        bool previousPState = false;


        float rotationAngleA{}, rotationAngleB{};
        glm::vec3 translationA{}, translationB{};
        glm::vec3 scaleA{}, scaleB{};



    private:
        // Add private members here
        //std::vector<Texture> luffyFrames; // Vector to store animation frames
        //int currentFrame = 0;
        //float frameDuration = 0.2f; // Adjust frame duration as needed
        //float frameTimer = 0.0f;
        //int totalFrames = 8; // Total number of frames in the animation
    };

}
#endif // ENGINE_GRAPHICS_H
