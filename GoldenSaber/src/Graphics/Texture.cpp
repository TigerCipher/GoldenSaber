﻿//  ------------------------------------------------------------------------------
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
//  File Name: Texture.cpp
//  Date File Created: 12/08/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Texture.h"

#include <cassert>
#include <stb_image.h>
#include <GL/glew.h>

namespace saber
{
texture::texture(const std::string& path)
{
    m_path = path;
    LOG_INFO("Loading texture from '{}'", path);

    i32 w, h, channels;
    stbi_set_flip_vertically_on_load(1);
    u8* data = stbi_load(path.c_str(), &w, &h, &channels, 0);

    if (data)
    {
        m_width  = w;
        m_height = h;

        GLenum internal_format = 0, data_format = 0;
        if (channels == 4)
        {
            internal_format = GL_RGBA8;
            data_format     = GL_RGBA;
        } else if (channels == 3)
        {
            internal_format = GL_RGB8;
            data_format     = GL_RGB;
        }

        m_internal_format = internal_format;
        m_format          = data_format;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
        glTextureStorage2D(m_id, 1, internal_format, m_width, m_height);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, data_format, GL_UNSIGNED_BYTE, data);


        stbi_image_free(data);
        LOG_INFO("Done.");
    } else
    {
        LOG_ERROR("Failed to load texture '{}'", path);
    }
}

texture::texture(u32 width, u32 height)
{
    m_width           = (i32) width;
    m_height          = (i32) height;
    m_internal_format = GL_RGBA8;
    m_format          = GL_RGBA;

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glTextureStorage2D(m_id, 1, m_internal_format, m_width, m_height);

    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
}


texture::~texture()
{
    glDeleteTextures(1, &m_id);
}

void texture::bind(u32 slot) const
{
    glBindTextureUnit(slot, m_id);
}

void texture::set_data(const void* data, u32 size) const
{
    assert((i32) size == m_width * m_height * (m_format == GL_RGBA ? 4 : 3) && "Data must contain entire texture");
    glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_format, GL_UNSIGNED_BYTE, data);
}


sprite::sprite(const ref<texture>& tex, const glm::vec2& min, const glm::vec2& max)
{
    m_texture      = tex;
    m_texcoords[0] = { min.x, min.y };
    m_texcoords[1] = { max.x, min.y };
    m_texcoords[2] = { max.x, max.y };
    m_texcoords[3] = { min.x, max.y };
}

void sprite::bind(u32 slot) const
{
    if (m_texture)
    {
        m_texture->bind(slot);
    }
}


ref<sprite> create_sprite_from_coords(const ref<texture>& texture, const glm::vec2& coords, const glm::vec2& cell_size,
                                      const glm::vec2& sprite_size)
{
    glm::vec2 min = { (coords.x * cell_size.x) / (f32)texture->width(), (coords.y * cell_size.y) / (f32)texture->height() };
    glm::vec2 max = { ((coords.x + sprite_size.x) * cell_size.x) / (f32)texture->width(),
                      ((coords.y + sprite_size.y) * cell_size.y) / (f32)texture->height() };

    return create_ref<sprite>(texture, min, max);
}


} // namespace saber