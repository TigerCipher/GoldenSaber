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
//  File Name: Buffer.cpp
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Buffer.h"


#include <GL/glew.h>

namespace saber
{


namespace
{

GLenum get_type(shader_data_type type)
{
    switch (type)
    {
    case shader_data_type::flt:
    case shader_data_type::flt2:
    case shader_data_type::flt3:
    case shader_data_type::flt4:
    case shader_data_type::mat3:
    case shader_data_type::mat4: return GL_FLOAT;
    case shader_data_type::integer:
    case shader_data_type::int2:
    case shader_data_type::int3:
    case shader_data_type::int4: return GL_INT;
    case shader_data_type::boolean: return GL_BOOL;
    case shader_data_type::none: break;
    }

    assert(false && "Unknown shader data type");
    return 0;
}

} // anonymous namespace

vertex_buffer::vertex_buffer(u32 size)
{
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
}

vertex_buffer::vertex_buffer(u32 size, const f32* vertices)
{
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

vertex_buffer::~vertex_buffer()
{
    glDeleteBuffers(1, &m_id);
}

void vertex_buffer::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void vertex_buffer::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void vertex_buffer::set_data(const void* data, u32 size) const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferSubData(GL_ARRAY_BUFFER, 0, size, data);
}

index_buffer::index_buffer(u32 count, const u32* indices)
{
    m_count = count;
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, (u64) count * sizeof(u32), indices, GL_STATIC_DRAW);
}

index_buffer::~index_buffer()
{
    glDeleteBuffers(1, &m_id);
}

void index_buffer::bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void index_buffer::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

vertex_array::vertex_array()
{
    glCreateVertexArrays(1, &m_id);
}

vertex_array::~vertex_array()
{
    glDeleteVertexArrays(1, &m_id);
}

void vertex_array::bind() const
{
    glBindVertexArray(m_id);
}

void vertex_array::unbind()
{
    glBindVertexArray(0);
}

void vertex_array::add_vertex_buffer(const ref<vertex_buffer>& buffer)
{
    assert(!buffer->layout().elements().empty() && "Vertex buffer has no layout");

    glBindVertexArray(m_id);
    buffer->bind();
    const auto& layout = buffer->layout();
    for (const auto& elem : layout)
    {
        switch (elem.type)
        {
        case shader_data_type::flt:
        case shader_data_type::flt2:
        case shader_data_type::flt3:
        case shader_data_type::flt4:
        {
            glEnableVertexAttribArray(m_vb_index);
            glVertexAttribPointer(m_vb_index, elem.component_count(), get_type(elem.type), elem.normalized ? GL_TRUE : GL_FALSE,
                                  layout.stride(), reinterpret_cast<const void*>(static_cast<uintptr_t>(elem.offset)));
            m_vb_index++;
            break;
        }
        case shader_data_type::integer:
        case shader_data_type::int2:
        case shader_data_type::int3:
        case shader_data_type::int4:
        case shader_data_type::boolean:
        {
            glEnableVertexAttribArray(m_vb_index);
            glVertexAttribIPointer(m_vb_index, elem.component_count(), get_type(elem.type), layout.stride(),
                                   reinterpret_cast<const void*>(static_cast<uintptr_t>(elem.offset)));
            m_vb_index++;
            break;
        }
        case shader_data_type::mat3:
        case shader_data_type::mat4:
        {
            u8 count = (u8) elem.component_count();
            for (u8 i = 0; i < count; ++i)
            {
                glEnableVertexAttribArray(m_vb_index);
                glVertexAttribPointer(m_vb_index, elem.component_count(), get_type(elem.type),
                                      elem.normalized ? GL_TRUE : GL_FALSE, layout.stride(),
                                      reinterpret_cast<const void*>((sizeof(f32) * count * i)));
                glVertexAttribDivisor(m_vb_index, 1);
                m_vb_index++;
            }
            break;
        }
        case shader_data_type::none: assert(false && "Unknown shader data type"); break;
        }
    }

    m_vertex_buffers.push_back(buffer);
}

void vertex_array::set_index_buffer(scope<index_buffer> buffer)
{
    glBindVertexArray(m_id);
    buffer->bind();
    m_index_buffer = std::move(buffer);
}

} // namespace saber