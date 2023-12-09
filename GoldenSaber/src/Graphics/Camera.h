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
//  File Name: Camera.h
//  Date File Created: 12/08/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Common.h"

#include <glm/glm.hpp>

namespace saber
{
class camera
{
public:
    camera(f32 left, f32 right, f32 bottom, f32 top);
    ~camera() = default;

    void set_projection(f32 left, f32 right, f32 bottom, f32 top);

    void set_position(const glm::vec3& position);
    void set_rotation(f32 rotation);

    void move(const glm::vec3& delta);
    void rotate(f32 delta);

    constexpr const glm::mat4& projection() const { return m_projection; }
    constexpr const glm::mat4& view() const { return m_view; }
    constexpr const glm::mat4& projection_view() const { return m_projection_view; }

    constexpr const glm::vec3& position() const { return m_position; }
    constexpr f32              rotation() const { return m_rotation; }

    void recalculate_view_matrix();

private:
    glm::mat4 m_projection{};
    glm::mat4 m_view{ 1.0f };
    glm::mat4 m_projection_view{};

    glm::vec3 m_position{};
    f32       m_rotation{};
};
} // namespace saber