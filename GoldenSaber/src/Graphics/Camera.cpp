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
//  File Name: Camera.cpp
//  Date File Created: 12/08/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace saber
{
camera::camera(f32 left, f32 right, f32 bottom, f32 top)
{
    m_projection      = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_projection_view = m_projection * m_view;
}

void camera::set_projection(f32 left, f32 right, f32 bottom, f32 top)
{
    m_projection      = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
    m_projection_view = m_projection * m_view;
}

void camera::set_position(const glm::vec3& position)
{
    m_position = position;
    recalculate_view_matrix();
}

void camera::set_rotation(f32 rotation)
{
    m_rotation = rotation;
    recalculate_view_matrix();
}

void camera::move(const glm::vec3& delta)
{
    m_position += delta;
    recalculate_view_matrix();
}

void camera::rotate(f32 delta)
{
    m_rotation += delta;
    recalculate_view_matrix();
}

void camera::recalculate_view_matrix()
{
    const glm::mat4 transform =
        glm::translate(glm::mat4(1.0f), m_position) * glm::rotate(glm::mat4(1.0f), m_rotation, glm::vec3(0, 0, 1));

    m_view            = glm::inverse(transform);
    m_projection_view = m_projection * m_view;
}
} // namespace saber