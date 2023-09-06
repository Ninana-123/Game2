#include "pch.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    //compiling the shader
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); //returns a pointer to the data inside stdstring
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char)); 
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int CreateShader(const std::string& VtxShdr, const std::string& FrgShdr)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VtxShdr);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FrgShdr);
    
    //linking both vs and fs into 1 program
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);//validation check whether program can execute

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;
}

int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1280, 720, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    //testing
    if (glewInit() != GLEW_OK)
        std::cout << "Error!" << std::endl;
    else
    {
    std::cout << glGetString(GL_VERSION) << std::endl;
    }

    //3 vertices (point on geometry) 
    float positions[6] = {
        -0.5f,-0.5f,
        0.0f,  0.5f,
        0.5f, -0.5f
    };

    //number of buffers to be generated
    unsigned int buffer;
    glGenBuffers(1, &buffer);

    //binding it to buffer object
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    //stores the position into the buffer data
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0); // first attrib, n0. of floats to represent vertex attrib,
                                                                           // type of data, already floats(the intended space) hence false,
                                                                           // the amount of bytes between each vertex, 

    std::string vertexShader =
        "#version 450 core\n"
        "\n"
        "layoyt(location = 0) in vec4 position"
        "\n"
        "void main()\n"
        "{\n"
        "gl_position = position;\n"
        "}\n";

    std::string fragmentShader =
        "#version 450 core\n"
        "\n"
        "layoyt(location = 0) out vec4 color"
        "\n"
        "void main()\n"
        "{\n"
        "color = vec4(1.0, 0.0, 0.0, 1.0);\n"
        "}\n";

    unsigned int shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //draw the current done buffer
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}