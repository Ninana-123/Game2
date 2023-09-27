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
        void InitialiseShader();
        void InitialiseTextures();
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
        bool isNewEntityMoved = false;
      

    private:
        Shader shader;
        Texture textureA;
        Texture textureB;
        float rotationAngleA{}, rotationAngleB{};
        glm::vec3 translationA{}, translationB{};
        glm::vec3 scaleA{}, scaleB{};
        
    };
}
#endif // ENGINE_GRAPHICS_H