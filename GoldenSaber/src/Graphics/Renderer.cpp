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
//  File Name: Renderer.cpp
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Renderer.h"


#include "Buffer.h"
#include "Shader.h"


#include <array>
#include <GL/glew.h>

namespace saber::gfx
{

namespace
{

struct quad_vertex
{
    glm::vec3 pos;
    glm::vec2 tex_coord;
    f32       tex_index;
};

constexpr u32 max_quads   = 10000;
constexpr u32 max_verts   = max_quads * 4;
constexpr u32 max_indices = max_quads * 6;


scope<shader>      quad_shader{};
ref<vertex_array>  quad_vtx_array{};
ref<vertex_buffer> quad_vtx_buffer{};

u32          quad_index_count{};
quad_vertex* quad_vtx_buffer_base{};
quad_vertex* quad_vtx_buffer_ptr{};

glm::vec4 quad_vtx_pos[4];

std::array<ref<texture>, 32> texture_slots{};
ref<texture>                 white_texture{};
u32                          texture_slot_index = 1; // white texture = 0

void start_batch()
{
    quad_index_count    = 0;
    quad_vtx_buffer_ptr = quad_vtx_buffer_base;
    texture_slot_index  = 1;
}

f32 get_texture_index(const ref<texture>& texture)
{
    f32 index{};

    for (u32 i = 1; i < texture_slot_index; ++i)
    {
        if (*texture_slots[i] == *texture.get())
        {
            index = (f32) i;
            break;
        }
    }

    if (index == 0.f)
    {
        index                             = (f32) texture_slot_index;
        texture_slots[texture_slot_index] = texture;
        texture_slot_index++;
    }

    return index;
}

void flush()
{
    if (!quad_index_count)
    {
        return;
    }
    const u32 size = (u32) ((u8*) quad_vtx_buffer_ptr - (u8*) quad_vtx_buffer_base);
    quad_vtx_buffer->set_data(quad_vtx_buffer_base, size);

    for (u32 i = 0; i < texture_slot_index; ++i)
    {
        texture_slots[i]->bind(i);
    }
    //quad_shader->bind();
    glDrawElements(GL_TRIANGLES, (i32) quad_index_count, GL_UNSIGNED_INT, nullptr);
    // keep track of draw calls for the sake of statistics
}

void reset_batch()
{
    flush();
    start_batch();
}

void create_quad(const glm::mat4& transform, const glm::vec2* texcoords, f32 tex_index)
{
    constexpr size_t quad_vtx_count = 4;
    for (size_t i = 0; i < quad_vtx_count; ++i)
    {
        quad_vtx_buffer_ptr->pos       = transform * quad_vtx_pos[i];
        quad_vtx_buffer_ptr->tex_coord = texcoords[i];
        quad_vtx_buffer_ptr->tex_index = tex_index;
        quad_vtx_buffer_ptr++;
    }

    quad_index_count += 6;
}

} // anonymous namespace


void init()
{
    quad_shader = create_scope<shader>("basic");
    quad_shader->load();

    quad_vtx_array  = create_ref<vertex_array>();
    quad_vtx_buffer = create_ref<vertex_buffer>(max_verts * (u32)sizeof(quad_vertex));
    quad_vtx_buffer->set_layout({
        {"aPosition", shader_data_type::flt3},
        {"aTexCoord", shader_data_type::flt2},
        {"aTexIndex",  shader_data_type::flt},
    });
    quad_vtx_array->add_vertex_buffer(quad_vtx_buffer);
    quad_vtx_buffer_base = new quad_vertex[max_verts];

    std::vector<u32> indices(max_indices);
    u32  offset  = 0;
    for (u32 i = 0; i < max_indices; i += 6)
    {
        indices[i + 0] = offset + 0;
        indices[i + 1] = offset + 1;
        indices[i + 2] = offset + 2;

        indices[i + 3] = offset + 2;
        indices[i + 4] = offset + 3;
        indices[i + 5] = offset + 0;

        offset += 4;
    }

    scope<index_buffer> ib = create_scope<index_buffer>(max_indices, indices.data());
    quad_vtx_array->set_index_buffer(std::move(ib));

    quad_vtx_pos[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
    quad_vtx_pos[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
    quad_vtx_pos[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
    quad_vtx_pos[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

    white_texture            = create_ref<texture>(1, 1);
    constexpr u32 white_data = 0xffffffff;
    white_texture->set_data(&white_data, sizeof(u32));

    //i32 samplers[32];
    //for (u32 i = 0; i < 32; ++i)
    //{
    //    samplers[i] = i;
    //}

    texture_slots[0] = white_texture;
}

void shutdown()
{
    quad_shader = nullptr;
}

void begin_scene(const camera& cam)
{
    quad_shader->bind();
    quad_shader->set_matrix("uProjView", cam.projection_view());
    start_batch();
}

void end_scene()
{
    flush();
}

void draw_sprite(const ref<sprite>& spr, const glm::mat4& transform, const glm::vec4& tint_color)
{
    if (quad_index_count >= max_indices)
    {
        reset_batch();
    }

    const f32        tex_index = get_texture_index(spr->get_texture());
    const glm::vec2* coords    = spr->tex_coords();
    create_quad(transform, coords, tex_index);
}

} // namespace saber::gfx