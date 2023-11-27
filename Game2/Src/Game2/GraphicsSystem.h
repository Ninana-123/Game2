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
#include "Camera.h"
#include "Animation.h"
#include "AssetManager.h"
#include "EntityManager.h"
#include "EditorCamera.h"
#include "Font.h"
#include "EditorFBO.h"

namespace Engine
{
    class GraphicsSystem : public System
    {
    public:
        /*!
        * \brief GraphicsSystem constructor.
        *
        * This constructor initializes a GraphicsSystem object and sets up the
        * default shader and textures.
        */
        GraphicsSystem();

        /*!
        * \brief GraphicsSystem constructor with asset manager and entity manager.
        *
        * This constructor initializes a GraphicsSystem object with an asset manager
        * and an entity manager, and sets up the default shader and textures.
        *
        * \param assetManager Shared pointer to the AssetManager.
        * \param entityManager Shared pointer to the EntityManager.
        */
        GraphicsSystem(std::shared_ptr<Engine::AssetManager> assetManager, std::shared_ptr<Engine::EntityManager> entityManager);

        /*!
        * \brief GraphicsSystem destructor.
        *
        * This destructor cleans up resources used by the GraphicsSystem.
        */
        ~GraphicsSystem();

        /*!
         * \brief Initialize the GraphicsSystem.
         *
         * This function initializes the GraphicsSystem by setting up OpenGL,
         * loading shaders, and initializing textures.
         */
        void Initialize() override;

        /*!
         * \brief Initialize the GLEW library.
         *
         * This function initializes the GLEW (OpenGL Extension Wrangler Library)
         * and logs the initialization result.
         */
        void InitializeGLEW();

        /*!
        * \brief Initialize the shader used for rendering.
        *
        * This function loads and initializes the shader used for rendering
        * and sets its initial uniform values.
        */
        void InitializeShader();

        /*!
        * \brief Initialize textures used for rendering.
        *
        * This function loads and initializes textures used for rendering.
        */
        void InitializeTextures();

        /*!
         * \brief Update the GraphicsSystem.
         *
         * This function updates the GraphicsSystem by rendering entities and handling
         * user input for toggling rendering modes.
         *
         * \param entities A pointer to a map of entities.
         */
        void Update(std::unordered_map<EntityID, std::unique_ptr<Entity>>* entities) override;

        /*!
         * \brief Updates the viewport and projection matrix.
         *
         * This function updates the OpenGL viewport to match the specified width and height.
         * It also updates the projection matrix to maintain the correct aspect ratio.
         *
         * \param width The width of the viewport.
         * \param height The height of the viewport.
         */
        void UpdateViewport(int width, int height);
       
        /*!
         * \brief Update the shader set used for rendering.
         *
         * This function updates the active shader set based on the current state.
         * It toggles between Shader Set 1 and Shader Set 2 and attempts to reinitialize the shaders.
         * The selection of the shader set depends on the internal state of the GraphicsSystem.
         *
         */
        void UpdateShaderSet();

        /*!
        * \brief Render a textured entity.
        *
        * This function renders a textured entity with the specified MVP matrix and alternates
        * between two textures based on time.
        *
        * \param mvpMatrix The Model-View-Projection matrix for rendering.
        */
        void RenderTexturedEntity(const glm::mat4& mvpMatrix, Entity* entity);

        /*!
         * \brief Render the background using the provided Model-View-Projection matrix.
         *
         * This function renders the background using the specified Model-View-Projection matrix.
         * The background is rendered using the shader program set for rendering textured entities.
         *
         * \param mvpMatrix The Model-View-Projection matrix for rendering.
         */
        void RenderBackground(const glm::mat4& mvpMatrix);

        /*!
         * \brief Render lines.
         *
         * This function renders lines with the specified MVP matrix.
         *
         * \param mvpMatrix The Model-View-Projection matrix for rendering.
         */
        void RenderLines(const glm::mat4& mvpMatrix);

        /*!
        * \brief Render a single line.
        *
        * This function renders a single line with the specified MVP matrix, start, and end positions.
        *
        * \param mvpMatrix The Model-View-Projection matrix for rendering.
        * \param lineStart The starting position of the line.
        * \param lineEnd The ending position of the line.
        */
        void RenderSingleLine(const glm::mat4& mvpMatrix, const glm::vec2& lineStart, const glm::vec2& lineEnd);

        /*!
         * \brief Toggle the rendering mode.
         *
         * This function toggles between textured and plain squares for rendering.
         */
        void ToggleRenderMode();

        /*!
         * \brief Toggles between two shader sets.
         *
         * This function toggles between Shader Set 1 and Shader Set 2. If the current active shader set
         * is Shader Set 1, it switches to Shader Set 2, and vice versa. After toggling, it attempts to
         * reinitialize the shaders based on the new active set.
         *
         * \note This function assumes that the shader object is properly initialized before calling it.
         *
         */
        void ToggleShaderSet();

        /*!
        * \brief Render a single colored square.
        *
        * This function renders a single colored square with the specified MVP matrix.
        *
        * \param mvpMatrix The Model-View-Projection matrix for rendering.
        */
        void DrawColoredSquare(const glm::mat4& mvpMatrix);
        //void SetMaxBatchSize(int maxSize);
        int screenWidth{}, screenHeight{};
      
        double animationStartTime{};
        double frameDuration{}; 


        EditorFBO editorFBO;

    private:
        Shader shader;
        std::vector<std::vector<Texture>> textures;

        float rotationAngleA{}, rotationAngleB{};
        glm::vec3 translationA{}, translationB{};
        glm::vec3 scaleA{}, scaleB{};
        glm::vec3 objectPosition{};

        /*!
         * \brief Setup the model matrix for an entity.
         *
         * This function sets up the model matrix for an entity based on translation,
         * rotation, and scale parameters.
         *
         * \param translation The translation vector.
         * \param rotationAngle The rotation angle in radians.
         * \param scale The scale vector.
         *
         * \return The model matrix for the entity.
         */
        glm::mat4 SetupModelMatrix(const glm::vec3& translation, float rotationAngle, const glm::vec3& scale);
        glm::mat4 proj{};
        glm::mat4 view{};
        glm::mat4 mvpMatrixForBackground = glm::mat4(1.0f);

        GLFWwindow* Window{};
        IndexBuffer ibQuad{};
        IndexBuffer ib;
        IndexBuffer ibLines;
        IndexBuffer ibBackground;

        VertexArray vaBackground;
        VertexArray vaQuadAndBackground{};
        VertexArray va;
        VertexArray vaLines;
        VertexArray vaSingleLine;

        font font;

        Renderer renderer;

        std::vector<float> vtx_positions_quad{};
        std::vector<unsigned int> indices_quad{};
        std::vector<float> vtx_positions_lines{};
        //std::vector<unsigned int> indices_lines;
        std::vector<float> vtx_positions_background{};
        std::vector<unsigned int> indices_background{};

        Camera m_Camera;
        EditorCamera m_EditorCamera;

        float CameraSpeed = 1.5f;
        float yOffset = 1.0f;
       

        float vtx_positions[16]{};
        unsigned int indices[6]{};
        double programStartTime = glfwGetTime();
        bool renderTexturedSquare = false;
        bool previousPState = false;
        bool renderTextureSquare = true;
        bool useShaderSet1 = true;
        bool previousSState = false;

        std::shared_ptr<Engine::AssetManager> assetManager;
        std::shared_ptr<Engine::EntityManager> entityManager;
    };
}
#endif // ENGINE_GRAPHICS_H