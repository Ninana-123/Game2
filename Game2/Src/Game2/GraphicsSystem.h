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
#include "CollisionSystem.h"
#include "Vector2d.h"

namespace Engine
{
    class GraphicsSystem : public System
    {
    public:

        GraphicsSystem();
        ~GraphicsSystem();

        void Initialize() override;
        void InitializeGLEW();
        void InitializeShader();
        void InitializeTextures();
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;
        void UpdateViewport(int width, int height);
        void RenderTexturedEntity(const glm::mat4& mvpMatrix);
        void RenderBackground();
        void RenderLines(const glm::mat4& mvpMatrix);
        void RenderSingleLine(const glm::mat4& mvpMatrix, const glm::vec2& lineStart, const glm::vec2& lineEnd);
        void ToggleRenderMode();
        void DrawColoredSquare(const glm::mat4& mvpMatrix);

    private:
        Shader shader;
        Texture textureA;
        Texture textureB;
        Texture textureC;

        float rotationAngleA{}, rotationAngleB{};
        glm::vec3 translationA{}, translationB{};
        glm::vec3 scaleA{}, scaleB{};

        glm::mat4 SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale);
        glm::mat4 proj{};
        glm::mat4 view{};
        glm::mat4 mvpMatrixForBackground = glm::mat4(1.0f);

        GLFWwindow* Window{};
        IndexBuffer ib;
        IndexBuffer ibLines;
        IndexBuffer ibBackground;

        VertexArray vaBackground;
        VertexArray va;
        VertexArray vaLines;
        VertexArray vaSingleLine;

        Renderer renderer;

        float vtx_positions[16]{};
        unsigned int indices[6]{};
        double programStartTime = glfwGetTime();
        bool renderTexturedSquare = false;
        bool previousPState = false;
        bool renderTextureSquare = true;
    };
}
#endif // ENGINE_GRAPHICS_H