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
//  File Name: Quad.cpp
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Quad.h"

#include <GL/glew.h>

namespace saber
{
quad::quad()
{
    m_vertices = {
        -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, // Bottom-left
        0.5f,  -0.5f, 0.0f, 1.0f, 1.0f, // Bottom-right
        0.5f,  0.5f,  0.0f, 1.0f, 0.0f, // Top-right
        -0.5f, 0.5f,  0.0f, 0.0f, 0.0f, // Top-left
    };
}

quad::quad(const sprite& spr)
{
    m_vertices = {
        -0.5f, -0.5f, 0.0f, spr.left(),  spr.bottom(), // Bottom-left
        0.5f,  -0.5f, 0.0f, spr.right(), spr.bottom(), // Bottom-right
        0.5f,  0.5f,  0.0f, spr.right(), spr.top(),    // Top-right
        -0.5f, 0.5f,  0.0f, spr.left(),  spr.top(),    // Top-left
    };
}

quad::~quad()
{
    glDeleteVertexArrays(1, &m_vao);
    glDeleteBuffers(1, &m_vbo);
}

void quad::create()
{
    glGenVertexArrays(1, &m_vao);
    glGenBuffers(1, &m_vbo);

    glBindVertexArray(m_vao);

    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(f32), m_vertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*) (3 * sizeof(f32)));
    glEnableVertexAttribArray(1);
}

void quad::draw() const
{
    glBindVertexArray(m_vao);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
}

} // namespace saber