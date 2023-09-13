/******************************************************************************/
/*!
\file		Graphics.cpp
\author 	Wayne Kwok Jun Lin
            Tristan Tham Rui Hong

\par    	email: k.junlinwayne@digipen.edu
                   t.tham@digipen.edu

\date   	August 29, 2023
\brief		This file contains 

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#include "pch.h"
#include "Graphics.h"
#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <unordered_map>

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    //testing
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    else
    {
    std::cout << glGetString(GL_VERSION) << std::endl;
    }
    {
        //3 vertices (point on geometry) 
        float positions[] = {
           -0.5f, -0.5f, //0
            0.5f, -0.5f, //1
            0.5f, -0.5f, //2
           -0.5f,  0.5f  //3
        };

        unsigned int indices[] = { //tells opengl how to render square w/o providing duplicate/redundant vertices
            0,1,2,
            2,3,0
        };

        unsigned int vao{};
        GLCall(glGenVertexArrays(1, &vao));
        GLCall(glBindVertexArray(vao));

        VertexArray va;
        VertexBuffer vb(positions, 4 * 2 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        va.AddBuffer(vb, layout);

        // type of data, already floats(the intended space) hence false,
        // the amount of bytes between each vertex, 
        IndexBuffer ib(indices, 6);

        //binding shader with shader id
        Shader shader("Resource/Shaders/Basic.shader");
        shader.Bind();
        //retrieving the location of u_Color variable
        shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

        va.Unbind();
        vb.Unbind();
        ib.Unbind();
        shader.Unbind();
        
        Renderer renderer;

        float r = 0.0f;
        float increment = 0.05f;
        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            renderer.Clear();
            shader.Bind();
            shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

            //drawn together in 1 call
            renderer.Draw(va, ib, shader);

            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;

            r += increment;

            /* Swap front and back buffers */
            GLCall(glfwSwapBuffers(window));

            /* Poll for and process events */
            glfwPollEvents();
        }
    }
    glfwTerminate();
    return 0;
}

namespace Engine
{
    Graphics::Graphics()
    {
        //constructor
        //initialize buffers;
        //unsigned int id{};
        //
    }

    Graphics::~Graphics()
    {
        //destructor
        //free everything here, assign everything to null and release all textures
    }

    void Graphics::Initialize()
    {
        //initialize default window width, height
        //
    }

    void Graphics::Update()
    {
        //polling events and update all object/entity graphics
    }


}