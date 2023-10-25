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
//Shader::Shader(const std::string& filepath, const std::string& filepath2)
//    : m_FilePath(filepath), m_FilePath2(filepath2), m_RendererID(0), m_IsInitialized(false)
//{
//}
Shader::Shader(const std::string& filepath1, const std::string& filepath2, const std::string& filepath3, const std::string& filepath4)
    : m_FilePath1(filepath1), m_FilePath2(filepath2), 
      m_FilePath3(filepath3), m_FilePath4(filepath4), 
      m_IsInitialized(false), m_CurrentShaderSet(1)
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
std::string Shader::LoadShaderSource(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::string shaderSource;
    std::string line;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            shaderSource += line + "\n";
        }
        file.close();
    }
    else
    {
        std::cerr << "Failed to open shader file: " << filepath << std::endl;
    }

    return shaderSource;
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

    // Load vertex shader source code from file
    std::string vertexShaderSource1 = LoadShaderSource(m_FilePath1);
    std::string vertexShaderSource2 = LoadShaderSource(m_FilePath3);

    // Load fragment shader source code from file
    std::string fragmentShaderSource1 = LoadShaderSource(m_FilePath2);
    std::string fragmentShaderSource2 = LoadShaderSource(m_FilePath4);

    // Create and compile shader programs for both sets
    unsigned int program1 = CreateShader(vertexShaderSource1, fragmentShaderSource1);
    unsigned int program2 = CreateShader(vertexShaderSource2, fragmentShaderSource2);

    // Check for shader compilation and linking errors for the first shader program
    CheckShaderCompilation(program1, "ShaderSet1");

    // Check for shader compilation and linking errors for the second shader program
    CheckShaderCompilation(program2, "ShaderSet2");

    // Store shader program IDs in the map
    m_RendererIDs[1] = program1;
    m_RendererIDs[2] = program2;

    m_IsInitialized = true;
}

void Shader::CheckShaderCompilation(unsigned int programID, const std::string& shaderSetName) {
    int success;
    char infoLog[512];
    GLCall(glGetProgramiv(programID, GL_LINK_STATUS, &success));
    if (!success) {
        GLCall(glGetProgramInfoLog(programID, 512, NULL, infoLog));
        std::cerr << "Shader program (" << shaderSetName << ") linking failed:\n" << infoLog << std::endl;
        // Handle the error as needed, e.g., return or throw an exception
    }
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
                type = ShaderType::VERTEX;
            else if (line.find("fragment") != std::string::npos)
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

    // Attach shaders and link the program
    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));
    GLCall(glLinkProgram(program));

    // Check for linking errors
    int success;
    GLCall(glGetProgramiv(program, GL_LINK_STATUS, &success));
    if (!success)
    {
        int length;
        GLCall(glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)_malloca(length * sizeof(char));
        GLCall(glGetProgramInfoLog(program, length, &length, message));
        std::cout << "Failed to link shader program!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteProgram(program));
        return 0;
    }

    // Validate the program
    GLCall(glValidateProgram(program));
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
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
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
    auto it = m_RendererIDs.find(m_CurrentShaderSet);
    if (it != m_RendererIDs.end())
    {
        unsigned int rendererID = it->second;
        if (rendererID != 0)
        {
            GLCall(glUseProgram(rendererID));

            GLenum error = glGetError();
            if (error != GL_NO_ERROR)
            {
                std::cerr << "[OpenGL Error] (" << error << "): glUseProgram(rendererID)" << std::endl;
                __debugbreak();
            }
        }
        else
        {
            std::cerr << "Attempting to use an invalid shader program!" << std::endl;
        }
    }
    else
    {
        std::cerr << "Shader set " << m_CurrentShaderSet << " is not initialized!" << std::endl;
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
    auto& uniformLocationCache = m_UniformLocationCaches[m_CurrentShaderSet];

    if (uniformLocationCache.find(name) != uniformLocationCache.end())
        return uniformLocationCache[name];

    unsigned int rendererID = m_RendererIDs[m_CurrentShaderSet];
    GLCall(int location = glGetUniformLocation(rendererID, name.c_str()));

    if (location == -1)
        std::cout << "Warning: Uniform '" << name << "' doesn't exist" << std::endl;

    uniformLocationCache[name] = location;
    return location;
}

void Shader::SetActiveShaderSet(int shaderSet)
{
    m_CurrentShaderSet = shaderSet;
}

void Shader::SetShaderProgram(int shaderSet, unsigned int programID) {
    m_RendererIDs[shaderSet] = programID;
}