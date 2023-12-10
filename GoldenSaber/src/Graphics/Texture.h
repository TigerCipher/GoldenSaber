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
//  File Name: Texture.h
//  Date File Created: 12/08/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Common.h"


#include <glm/glm.hpp>

namespace saber
{
class texture
{
public:
    texture(const std::string& path);
    texture(u32 width, u32 height);
    ~texture();

    void bind(u32 slot = 0) const;
    void set_data(const void* data, u32 size) const;

    constexpr u32 width() const { return m_width; }
    constexpr u32 height() const { return m_height; }
    constexpr u32 id() const { return m_id; }

    bool operator==(const texture& other) const { return m_id == other.m_id; }

private:
    u32         m_id{};
    i32         m_width{};
    i32         m_height{};
    u32         m_format{};
    u32         m_internal_format{};
    std::string m_path{};
};


class sprite
{
public:
    sprite(const ref<texture>& tex, const glm::vec2& min, const glm::vec2& max);
    ~sprite() = default;

    void bind(u32 slot = 0) const;

    constexpr const ref<texture>& get_texture() const { return m_texture; }
    constexpr const glm::vec2* tex_coords() const { return m_texcoords; }

private:
    ref<texture> m_texture{};
    glm::vec2    m_texcoords[4];
};

ref<sprite> create_sprite_from_coords(const ref<texture>& texture, const glm::vec2& coords, const glm::vec2& cell_size, const glm::vec2& sprite_size = {1, 1});

} // namespace saber