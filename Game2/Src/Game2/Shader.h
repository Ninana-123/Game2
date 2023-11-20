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
    //Shader(const std::string& filepath, const std::string& filepath2);
    Shader(const std::string& filepath1, const std::string& filepath2, const std::string& filepath3, const std::string& filepath4, const std::string& filepath5, const std::string& filepath6);
    ~Shader();

    //void LoadShader(const std::string& filepath);
    std::string LoadShaderSource(const std::string& filepath);
    // Load shader source from a file
    void Initialize();  // Compile and set up the shader

    void Bind() const;
    void Unbind() const;

    void CheckShaderCompilation(unsigned int programID, const std::string& shaderSetName);

    void SetActiveShaderSet(int shaderSet);

    // Set uniforms
    void SetUniform1i(const std::string& name, int value);
    void SetUniform1f(const std::string& name, float value);
    //void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniformMat4f(const std::string& name, const glm::mat4& matrix);
    void SetUniform2f(const std::string& name, const glm::vec2& vector);

    void SetShaderProgram(int shaderSet, unsigned int programID);

    unsigned int CreateShader(const std::string& VtxShdr, const std::string& FrgShdr);
    int GetCurrentShaderSet() const;
    unsigned int GetID() const;

private:
    ShaderProgramSource ParseShader(const std::string& filepath);
    unsigned int CompileShader(unsigned int type, const std::string& source);
    int GetUniformLocation(const std::string& name);
};
#endif ENGINE_SHADER_H