//  ------------------------------------------------------------------------------
//
//  GoldenSaber
//     Copyright 2023 Matthew Rogers
//
//     Licensed under the Apache License, Version 2.0 (the "License");
//     you may not use this file except in compliance with the License.
//     You may obtain a copy of the License at
//
//         http://www.apache.org/licenses/LICENSE-2.0
//
//     Unless required by applicable law or agreed to in writing, software
//     distributed under the License is distributed on an "AS IS" BASIS,
//     WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//     See the License for the specific language governing permissions and
//     limitations under the License.
//
//  File Name: Shader.cpp
//  Date File Created: 12/07/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Shader.h"

#include <fstream>
#include <format>
#include <vector>

#include <GL/glew.h>

namespace saber
{

namespace
{

u32 load_from_binary(const std::string& name, GLenum shader_type)
{
    std::ifstream file{ std::format("./assets/shaders/{}.{}.spv", name, shader_type == GL_FRAGMENT_SHADER ? "frag" : "vert"),
                        std::ios::ate | std::ios::binary };

    if (!file.is_open())
    {
        LOG_ERROR("Failed to open shader file: {}", name);
        return invalid_u32;
    }

    LOG_INFO("Loading shader '{}.{}.spv'", name, shader_type == GL_FRAGMENT_SHADER ? "frag" : "vert");
    const size_t      filesize = file.tellg();
    std::vector<char> buffer(filesize);
    file.seekg(0);
    file.read(buffer.data(), filesize);
    file.close();

    const u32 id = glCreateShader(shader_type);
    glShaderBinary(1, &id, GL_SHADER_BINARY_FORMAT_SPIR_V, buffer.data(), (GLsizei) filesize);
    glSpecializeShader(id, "main", 0, nullptr, nullptr);

    GLint status;
    glGetShaderiv(id, GL_COMPILE_STATUS, &status);
    if (!status)
    {
        GLchar info_log[1024];
        glGetShaderInfoLog(id, sizeof(info_log), nullptr, info_log);
        LOG_ERROR("Failed to compile shader: {}", info_log);
        glDeleteShader(id);
        return invalid_u32;
    }
    return id;
}

} // anonymous namespace

shader::~shader()
{
    LOG_DEBUG("Deleting shader '{}'", m_name);
    glDeleteShader(m_vertex_shader);
    glDeleteShader(m_fragment_shader);
    glDeleteProgram(m_id);
}

bool shader::load()
{
    LOG_INFO("Loading shader '{}'", m_name);
    m_vertex_shader   = load_from_binary(m_name, GL_VERTEX_SHADER);
    m_fragment_shader = load_from_binary(m_name, GL_FRAGMENT_SHADER);

    if (m_vertex_shader == invalid_u32 || m_fragment_shader == invalid_u32)
    {
        return false;
    }

    m_id = glCreateProgram();
    glAttachShader(m_id, m_vertex_shader);
    glAttachShader(m_id, m_fragment_shader);
    glLinkProgram(m_id);

    GLint status;
    glGetProgramiv(m_id, GL_LINK_STATUS, &status);
    if (!status)
    {
        GLchar info_log[1024];
        glGetProgramInfoLog(m_id, sizeof(info_log), nullptr, info_log);
        LOG_ERROR("Failed to link shader: {}", info_log);
        return false;
    }
    LOG_INFO("Done.");
    return true;
}

void shader::bind() const
{
    glUseProgram(m_id);
}

void shader::set_uniform(const std::string& name, const f32* data, u32 count) const
{
    if (const GLint location = glGetUniformLocation(m_id, name.c_str()); location != -1)
    {
        switch (count)
        {
        case 1: glUniform1fv(location, 1, data); break;
        case 2: glUniform2fv(location, 1, data); break;
        case 3: glUniform3fv(location, 1, data); break;
        case 4: glUniform4fv(location, 1, data); break;
        default: LOG_ERROR("Invalid uniform count: {}", count); break;
        }
    } else
    {
        LOG_ERROR("Failed to find uniform: {}", name);
    }
}

void shader::set_matrix(const std::string& name, const glm::mat4& matrix) const
{
    if (const GLint location = glGetUniformLocation(m_id, name.c_str()); location != -1)
    {
        glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
    } else
    {
        LOG_ERROR("Failed to find uniform: {}", name);
    }
}

} // namespace saber