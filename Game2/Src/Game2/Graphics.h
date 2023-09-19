#pragma once
#include"pch.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Texture.h"
#include "glm/gtc/matrix_transform.hpp"

//#include "imgui.h"
//#include "imgui_impl_glfw_gl3.h"


namespace Engine
{

    class Graphics
    {
    public:
        Graphics();
        ~Graphics();

        void Initialize();
        void Update();
        // Add other functions here


        GLFWwindow* window;

        float rotationAngle = 0.0f;

        Renderer renderer;
        VertexArray va{ 1 };
        IndexBuffer ib;
        glm::mat4 proj;
        glm::mat4 view;

        Texture luffyTexture;
        Texture zoroTexture;
    private:
        // Add private members here
    };

} // namespace Engine
