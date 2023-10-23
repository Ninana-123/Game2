/******************************************************************************/
/*!
\file		Shader.cpp
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the implementation of the Shader class, which
            represents an OpenGL shader program.

            Copyright (C) 2023 DigiPen Institute of Technology.
            Reproduction or disclosure of this file or its contents without the prior
            written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#include "pch.h"
#include "Shader.h"
#include "Renderer.h"

/*!
 * \brief Shader constructor.
 * \param filepath The file path to the shader source code.
 *
 * This constructor initializes a Shader object with the provided file path.
 */
Shader::Shader(const std::string& filepath)
    : m_FilePath(filepath), m_RendererID(0), m_IsInitialized(false)
{
}

/*!
 * \brief Shader destructor.
 *
 * This destructor cleans up shader resources when the Shader object is destroyed.
 */
Shader::~Shader()
{
}

/*!
 * \brief Load shader source code from a file.
 * \param filepath The file path to the shader source code.
 *
 * This function loads shader source code from a file and updates the Shader object's file path.
 */
void Shader::LoadShader(const std::string& filepath)
{
    m_FilePath = filepath;
    m_IsInitialized = false;
}

/*!
 * \brief Initialize the shader program.
 *
 * This function initializes the shader program, compiles the shaders, and links the program.
 * It also performs error checking for shader compilation and linking.
 */
void Shader::Initialize()
{
    if (m_IsInitialized)
        return;  // Shader is already initialized

    ShaderProgramSource source = ParseShader(m_FilePath);
    m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);

    // Check for shader compilation and linking errors
    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog));
        std::cerr << "Shader program linking failed:\n" << infoLog << std::endl;
        // Handle the error as needed, e.g., return or throw an exception
    }

    m_IsInitialized = true;
}

/*!
 * \brief Parse a shader source file.
 * \param filepath The file path to the shader source code.
 * \return A structure containing the vertex and fragment shader source code.
 *
 * This function reads and parses a shader source file to separate the vertex and fragment
 * shader source code into distinct strings.
 */
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
    std::ifstream stream(filepath);

    enum class ShaderType
    {
        NONE = -1, VERTEX = 0, FRAGMENT = 1
    };

    std::string line;
    std::stringstream ss[2];
    ShaderType type = ShaderType::NONE;

    while (getline(stream, line))
    {
        if (line.find("shader") != std::string::npos)
        {
            if (line.find("vertex") != std::string::npos)
                // Set mode to vertex
                type = ShaderType::VERTEX;

            else if (line.find("fragment") != std::string::npos)
                // Set mode to fragment
                type = ShaderType::FRAGMENT;
        }
        else
        {
            ss[(int)type] << line << '\n';
        }
    }

    return { ss[0].str(), ss[1].str() };
}

/*!
 * \brief Create an OpenGL shader program.
 * \param VtxShdr The vertex shader source code.
 * \param FrgShdr The fragment shader source code.
 * \return The ID of the created shader program.
 *
 * This function creates an OpenGL shader program, compiles the provided vertex and fragment shaders,
 * attaches them to the program, and links them into a complete shader program.
 */
unsigned int Shader::CreateShader(const std::string& VtxShdr, const std::string& FrgShdr)
{
    // Create a shader program and attach vertex and fragment shaders
    GLCall(unsigned int program = glCreateProgram());
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VtxShdr);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FrgShdr);

    // Link both vs and fs into one program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program)); // Validation check whether the program can execute

    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}

/*!
 * \brief Compile an OpenGL shader.
 * \param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
 * \param source The shader source code.
 * \return The ID of the compiled shader.
 *
 * This function compiles an OpenGL shader of the specified type with the given source code.
 * It performs error checking for shader compilation and returns the ID of the compiled shader.
 */
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    // Compile the shader
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str(); // Returns a pointer to the data inside std::string
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE)
    {
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}

/*!
 * \brief Bind the shader program for rendering.
 *
 * This function binds the OpenGL shader program for rendering.
 */
void Shader::Bind() const
{
    if (m_RendererID == 0) {
        std::cerr << "Attempting to use an invalid shader program!" << std::endl;
        return;
    }

    GLCall(glUseProgram(m_RendererID));

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "[OpenGL Error] (" << error << "): glUseProgram(m_RendererID)" << std::endl;
        __debugbreak();  // This will trigger a debugger break to help you pinpoint the issue.
    }
}

/*!
 * \brief Unbind any currently bound shader program.
 *
 * This function unbinds any currently bound OpenGL shader program.
 */
void Shader::Unbind() const
{
    GLCall(glUseProgram(0));
}

/*!
 * \brief Set a uniform integer value in the shader program.
 * \param name The name of the uniform variable.
 * \param value The integer value to set.
 *
 * This function sets a uniform integer value in the shader program.
 */
void Shader::SetUniform1i(const std::string& name, int value)
{
    GLCall(glUniform1i(GetUniformLocation(name), value));
}

/*!
 * \brief Set a uniform float value in the shader program.
 * \param name The name of the uniform variable.
 * \param value The float value to set.
 *
 * This function sets a uniform float value in the shader program.
 */
void Shader::SetUniform1f(const std::string& name, float value)
{
    GLCall(glUniform1f(GetUniformLocation(name), value));
}

/*!
 * \brief Set a uniform 4x4 matrix in the shader program.
 * \param name The name of the uniform variable.
 * \param matrix The 4x4 matrix to set.
 *
 * This function sets a uniform 4x4 matrix in the shader program.
 */
void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& matrix)
{
    GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}

/*!
 * \brief Set a uniform 4-component float vector in the shader program.
 * \param name The name of the uniform variable.
 * \param v0 The first component.
 * \param v1 The second component.
 * \param v2 The third component.
 * \param v3 The fourth component.
 *
 * This function sets a uniform 4-component float vector in the shader program.
 */
void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
    GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

/*!
 * \brief Get the location of a uniform variable in the shader program.
 * \param name The name of the uniform variable.
 * \return The location of the uniform variable.
 *
 * This function retrieves the location of a uniform variable in the shader program
 * and caches it for future use to improve performance.
 */
int Shader::GetUniformLocation(const std::string& name)
{
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];
    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1)
        std::cout << "Warning: Uniform '" << name << "' doesn't exist" << std::endl;
    m_UniformLocationCache[name] = location;
    return location;
}
