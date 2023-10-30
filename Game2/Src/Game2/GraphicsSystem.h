/******************************************************************************/
/*!
\file		GraphicSystem.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the GraphicsSystem class.
            It handles initializing OpenGL, rendering entities, and managing
            rendering modes. 

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
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

        //void Initialize(const std::vector<float>& positions, const std::vector<unsigned int>& indices) override;
        void Initialize() override;
        //void Initialize(const std::vector<float>& quadPositions, const std::vector<float>& linePositions, const std::vector<float>& backgroundPositions) override;
        void InitializeGLEW();
        void InitializeShader();
        void InitializeTextures();
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;
        void UpdateViewport(int width, int height);
        void RenderTexturedEntity(const glm::mat4& mvpMatrix);
        void RenderBatchedEntities(const std::vector<glm::vec2>& positions, const std::vector<glm::vec2>& texCoords,
            const std::vector<float>& texIndices);
        void RenderBackground(const glm::mat4& mvpMatrix);
        void RenderLines(const glm::mat4& mvpMatrix);
        void RenderSingleLine(const glm::mat4& mvpMatrix, const glm::vec2& lineStart, const glm::vec2& lineEnd);
        void ToggleRenderMode();
        void ToggleShaderSet();
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
        IndexBuffer ibQuad;
        IndexBuffer ibBackground;

        VertexArray vaBackground;
        VertexArray vaQuad;
        VertexArray vaLines;

        Renderer renderer;

        std::vector<float> vtx_positions_quad{};
        std::vector<unsigned int> indices_quad{};
        std::vector<float> vtx_positions_lines{};
        //std::vector<unsigned int> indices_lines;
        std::vector<float> vtx_positions_background{};
        std::vector<unsigned int> indices_background{};

        float vtx_positions[16]{};
        unsigned int indices[6]{};
        double programStartTime = glfwGetTime();
        bool renderTexturedSquare = false;
        bool previousPState = false;
        bool renderTextureSquare = true;
        bool useShaderSet1 = true;
        bool previousSState = false;
    };
}
#endif // ENGINE_GRAPHICS_H