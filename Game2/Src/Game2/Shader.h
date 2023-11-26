/******************************************************************************/
/*!
\file		Shader.h
\author 	Wayne Kwok Jun Lin
\par    	email: k.junlinwayne@digipen.edu
\date   	August 29, 2023
\brief		This file contains the Shader class
          

Copyright (C) 2023 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior
written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/
#pragma once

#ifndef ENGINE_SHADER_H
#define ENGINE_SHADER_H

#include <string>
#include <unordered_map>
#include "glm/glm.hpp"

struct ShaderProgramSource
{
    std::string VertexSource;
    std::string FragmentSource;
};

class Shader
{
private:
    std::string m_FilePath1;             // Filepath to shader source files
    std::string m_FilePath2;
    std::string m_FilePath3;
    std::string m_FilePath4;
    std::string m_FilePath5;
    std::string m_FilePath6;
    //unsigned int m_RendererID1;          // Shader program ID
    //unsigned int m_RendererID2;
    bool m_IsInitialized;               // Flag to track initialization
    std::unordered_map<int, std::unordered_map<std::string, int>> m_UniformLocationCaches; // Caching for uniforms of different shader sets
    std::unordered_map<int, unsigned int> m_RendererIDs;                                    // Shader program IDs for different shader sets
    int m_CurrentShaderSet;             // Current active shader set (1 or 2)

public:
    /*!
     * \brief Shader constructor.
     * \param filepath The file path to the shader source code.
     *
     * This constructor initializes a Shader object with the provided file path.
     */
    Shader(const std::string& filepath1, const std::string& filepath2, const std::string& filepath3, const std::string& filepath4, const std::string& filepath5, const std::string& filepath6);
    
    /*!
     * \brief Shader destructor.
     *
     * This destructor cleans up shader resources when the Shader object is destroyed.
     */
    ~Shader();

    /*!
     * \brief Load shader source code from a file.
     * \param filepath The file path to the shader source code.
     *
     * This function loads shader source code from a file and updates the Shader object's file path.
     */
    std::string LoadShaderSource(const std::string& filepath);
   
    /*!
     * \brief Initialize the shader program.
     *
     * This function initializes the shader program, compiles the shaders, and links the program.
     * It also performs error checking for shader compilation and linking.
     */
    void Initialize();  // Compile and set up the shader


    /*!
     * \brief Bind the shader program for rendering.
     *
     * This function binds the OpenGL shader program for rendering.
     */
    void Bind() const;

    /*!
     * \brief Unbind any currently bound shader program.
     *
     * This function unbinds any currently bound OpenGL shader program.
     */
    void Unbind() const;

    /*!
     * \brief Check shader compilation status and log any errors.
     * \param programID The ID of the shader program.
     * \param shaderSetName The name of the shader set.
     *
     * This function checks the compilation status of shaders in a program and logs any errors.
     */
    void CheckShaderCompilation(unsigned int programID, const std::string& shaderSetName);

    /*!
     * \brief Set the active shader set.
     * \param shaderSet The shader set to activate (1 or 2).
     *
     * This function sets the active shader set.
     */
    void SetActiveShaderSet(int shaderSet);

    /*!
     * \brief Set a uniform integer value in the shader program.
     * \param name The name of the uniform variable.
     * \param value The integer value to set.
     *
     * This function sets a uniform integer value in the shader program.
     */
    void SetUniform1i(const std::string& name, int value);

    /*!
     * \brief Set a uniform float value in the shader program.
     * \param name The name of the uniform variable.
     * \param value The float value to set.
     *
     * This function sets a uniform float value in the shader program.
     */
    void SetUniform1f(const std::string& name, float value);

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
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);

    /*!
     * \brief Set a uniform 4x4 matrix in the shader program.
     * \param name The name of the uniform variable.
     * \param matrix The 4x4 matrix to set.
     *
     * This function sets a uniform 4x4 matrix in the shader program.
     */
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);

    /*!
     * \brief Set a uniform 2-component float vector in the shader program.
     * \param name The name of the uniform variable.
     * \param vector The 2-component float vector to set.
     *
     * This function sets a uniform 2-component float vector in the shader program.
     */
    void SetUniform2f(const std::string& name, const glm::vec2& vector);

    /*!
     * \brief Set the shader program for a specific shader set.
     * \param shaderSet The shader set (1 or 2).
     * \param programID The ID of the shader program.
     *
     * This function sets the shader program for a specific shader set.
     */
    void SetShaderProgram(int shaderSet, unsigned int programID);

    /*!
     * \brief Create an OpenGL shader program.
     * \param VtxShdr The vertex shader source code.
     * \param FrgShdr The fragment shader source code.
     * \return The ID of the created shader program.
     *
     * This function creates an OpenGL shader program, compiles the provided vertex and fragment shaders,
     * attaches them to the program, and links them into a complete shader program.
     */
    unsigned int CreateShader(const std::string& VtxShdr, const std::string& FrgShdr);
    /*!
    * \brief Get the current active shader set.
    * \return The current active shader set (1 or 2).
    *
    * This function returns the current active shader set.
    */
    int GetCurrentShaderSet() const;

    /*!
     * \brief Get the ID of the shader program.
     * \return The ID of the shader program.
     *
     * This function returns the ID of the shader program.
     */
    unsigned int GetID() const;

private:
    /*!
     * \brief Parse a shader source file.
     * \param filepath The file path to the shader source code.
     * \return A structure containing the vertex and fragment shader source code.
     *
     * This function reads and parses a shader source file to separate the vertex and fragment
     * shader source code into distinct strings.
     */
    ShaderProgramSource ParseShader(const std::string& filepath);

    /*!
     * \brief Compile an OpenGL shader.
     * \param type The type of shader (GL_VERTEX_SHADER or GL_FRAGMENT_SHADER).
     * \param source The shader source code.
     * \return The ID of the compiled shader.
     *
     * This function compiles an OpenGL shader of the specified type with the given source code.
     * It performs error checking for shader compilation and returns the ID of the compiled shader.
     */
    unsigned int CompileShader(unsigned int type, const std::string& source);

    /*!
     * \brief Get the location of a uniform variable in the shader program.
     * \param name The name of the uniform variable.
     * \return The location of the uniform variable.
     *
     * This function retrieves the location of a uniform variable in the shader program
     * and caches it for future use to improve performance.
     */
    int GetUniformLocation(const std::string& name);
};
#endif ENGINE_SHADER_H