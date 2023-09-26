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
#include "TransformComponent.h"
#include "Entity.h"

namespace Engine
{
    class Graphics : public System
    {
    public:
        Graphics();
        ~Graphics();

        void Initialize() override;
        void Update(Entity* entity) override;
        void InitializeGLEW();
        void UpdateViewport(int width, int height);
        void UpdateTransformations(int key);
        void ToggleRenderMode();
        void InitAndBindShader();
        void InitAndBindTextures();
        glm::mat4 SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale);

        GLFWwindow* Window{};
        IndexBuffer ib;
        Renderer renderer;
        VertexArray va;
        glm::mat4 proj{};
        glm::mat4 view{};
        float vtx_postions[16]{};
        unsigned int indices[6]{};
        double programStartTime = glfwGetTime();
        bool renderTexturedSquare = false;
        bool previousPState = false;
        bool renderTextureSquare = true;

    private:
        Shader shader;
        Texture luffyTexture;
        Texture zoroTexture;
        float rotationAngleA{}, rotationAngleB{};
        glm::vec3 translationA{}, translationB{};
        glm::vec3 scaleA{}, scaleB{};
        
    };
}
#endif // ENGINE_GRAPHICS_H