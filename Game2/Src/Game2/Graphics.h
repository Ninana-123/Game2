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
#include"Collision.h"
#include"Vector2d.h"

namespace Engine
{
    class Graphics : public System
    {
    public:
        Graphics();
        ~Graphics();

        void Initialize() override;
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

        void InitializeGLEW();
        void UpdateViewport(int width, int height);
        // void UpdateTransformations(int key, glm::vec3 translation, glm::vec3 scale, float rotation);
        void ToggleRenderMode();
        void InitializeShader();
        void InitializeTextures();
        void RenderTexturedEntity(const glm::mat4& mvpMatrix);
        void RenderLines(const glm::mat4& mvpMatrix);
        void DrawColoredSquare(const glm::mat4& mvpMatrix);
        void RenderBackground();
        void RenderSingleLine(const glm::mat4& mvpMatrix, const glm::vec2& lineStart, const glm::vec2& lineEnd);

    private:
        Shader shader;
        Texture textureA;
        Texture textureB;
        Texture textureC;

        float rotationAngleA{}, rotationAngleB{};
        glm::vec3 translationA{}, translationB{};
        glm::vec3 scaleA{}, scaleB{};

        glm::mat4 SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale);

        GLFWwindow* Window{};
        IndexBuffer ib;
        IndexBuffer ibLines;
        IndexBuffer ibBackground;

        VertexArray vaBackground;
        VertexArray va;
        VertexArray vaLines;
        VertexArray vaSingleLine;


        Renderer renderer;
        glm::mat4 proj{};
        glm::mat4 view{};

        VertexBuffer* aabbMeshVB;  // Declare as pointer
        VertexBufferLayout* aabbMeshLayout;  // Declare as pointer
        glm::mat4 mvpMatrixForBackground = glm::mat4(1.0f);



        float vtx_postions[16]{};
        unsigned int indices[6]{};
        double programStartTime = glfwGetTime();
        bool renderTexturedSquare = false;
        bool previousPState = false;
        bool renderTextureSquare = true;
    };
}
#endif // ENGINE_GRAPHICS_H