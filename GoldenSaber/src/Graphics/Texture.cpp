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
//  File Name: Texture.cpp
//  Date File Created: 12/08/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Texture.h"

#include <stb_image.h>
#include <GL/glew.h>

namespace saber
{
texture::texture(const std::string& path)
{
    m_path = path;
    LOG_INFO("Loading texture from '{}'", path);

    i32 w, h, channels;
    //stbi_set_flip_vertically_on_load(1);
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

        glGenTextures(1, &m_id);
        glBindTexture(GL_TEXTURE_2D, m_id);
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, m_width, m_height, 0, data_format, GL_UNSIGNED_BYTE, data);

        glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);


        stbi_image_free(data);
        LOG_INFO("Done.");
    } else
    {
        LOG_ERROR("Failed to load texture '{}'", path);
    }
}

texture::texture(u32 width, u32 height)
{
    m_width  = width;
    m_height = height;

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
    glBindTexture(GL_TEXTURE_2D, m_id);
}

sprite::sprite(const ref<texture>& tex, u32 x, u32 y, u32 width, u32 height) : m_texture(tex)
{
    m_left   = (f32) x * (f32)width / (f32) tex->width();
    m_right  = (f32) (x * width + width) / (f32) tex->width();
    m_top    = (f32) y * (f32)height / (f32) tex->height();
    m_bottom = (f32) (y * height + height) / (f32) tex->height();
}

void sprite::bind(u32 slot) const
{
    if (m_texture)
    {
        m_texture->bind(slot);
    }
}

} // namespace saber