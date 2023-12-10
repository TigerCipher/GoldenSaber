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
//  File Name: Buffer.h
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Common.h"


#include <cassert>
#include <vector>

namespace saber
{

enum class shader_data_type
{
    none = 0,
    flt,
    flt2,
    flt3,
    flt4,
    mat3,
    mat4,
    integer,
    int2,
    int3,
    int4,
    boolean
};

inline u32 shader_data_type_size(shader_data_type type)
{
    switch (type)
    {
    case shader_data_type::flt: return 4;
    case shader_data_type::flt2: return 4 * 2;
    case shader_data_type::flt3: return 4 * 3;
    case shader_data_type::flt4: return 4 * 4;
    case shader_data_type::mat3: return 4 * 3 * 3;
    case shader_data_type::mat4: return 4 * 4 * 4;
    case shader_data_type::integer: return 4;
    case shader_data_type::int2: return 4 * 2;
    case shader_data_type::int3: return 4 * 3;
    case shader_data_type::int4: return 4 * 4;
    case shader_data_type::boolean: return 1;
    case shader_data_type::none: assert(false && "Unknown shader data type"); return 0;
    }

    assert(false && "Unknown shader data type");
    return 0;
}

struct buffer_element
{
    std::string      name;
    shader_data_type type;
    u32              size;
    u32              offset{ 0 };
    bool             normalized{ false };

    buffer_element() = default;
    buffer_element(std::string name, shader_data_type type) : name(std::move(name)), type(type), size(shader_data_type_size(type))
    {}

    u32 component_count() const
    {
        switch (type)
        {
        case shader_data_type::flt: return 1;
        case shader_data_type::flt2: return 2;
        case shader_data_type::flt3: return 3;
        case shader_data_type::flt4: return 4;
        case shader_data_type::mat3: return 3; // * 3;
        case shader_data_type::mat4: return 4; // * 4;
        case shader_data_type::integer: return 1;
        case shader_data_type::int2: return 2;
        case shader_data_type::int3: return 3;
        case shader_data_type::int4: return 4;
        case shader_data_type::boolean: return 1;
        case shader_data_type::none: assert(false && "Unknown shader data type"); return 0;
        }

        return 0;
    }
};


class buffer_layout
{
public:
    buffer_layout() = default;
    buffer_layout(const std::initializer_list<buffer_element>& elems) : m_elements(elems) { calculate_offsets_and_stride(); }

    constexpr const std::vector<buffer_element>& elements() const { return m_elements; }
    constexpr u32                                stride() const { return m_stride; }

    std::vector<buffer_element>::iterator begin() { return m_elements.begin(); }
    std::vector<buffer_element>::iterator end() { return m_elements.end(); }

    std::vector<buffer_element>::const_iterator begin() const { return m_elements.begin(); }
    std::vector<buffer_element>::const_iterator end() const { return m_elements.end(); }

private:
    std::vector<buffer_element> m_elements{};
    u32                         m_stride{};

    void calculate_offsets_and_stride()
    {
        u32 offset = 0;
        m_stride   = 0;
        for (auto& e : m_elements)
        {
            e.offset = offset;
            offset += e.size;
            m_stride += e.size;
        }
    }
};

class vertex_buffer
{
public:
    vertex_buffer() = default;
    vertex_buffer(u32 size);
    vertex_buffer(u32 size, const f32* vertices);
    ~vertex_buffer();

    void        bind() const;
    static void unbind();

    void set_layout(const buffer_layout& layout) { m_layout = layout; }

    constexpr const buffer_layout& layout() const { return m_layout; }

    void set_data(const void* data, u32 size) const;

private:
    buffer_layout m_layout{};
    u32           m_id{};
};

class index_buffer
{
public:
    index_buffer() = default;
    index_buffer(u32 count, const u32* indices);
    ~index_buffer();

    void        bind() const;
    static void unbind();

    constexpr u32 count() const { return m_count; }

private:
    u32 m_id{};
    u32 m_count{};
};

class vertex_array
{
public:
    vertex_array();
    ~vertex_array();

    void        bind() const;
    static void unbind();

    void add_vertex_buffer(const ref<vertex_buffer>& buffer);
    void set_index_buffer(scope<index_buffer> buffer);

    constexpr const scope<index_buffer>& get_index_buffer() const { return m_index_buffer; }

    constexpr const std::vector<ref<vertex_buffer>>& vertex_buffers() const { return m_vertex_buffers; }

private:
    scope<index_buffer>             m_index_buffer{};
    u32                             m_id{};
    u32                             m_vb_index{};
    std::vector<ref<vertex_buffer>> m_vertex_buffers{};
};

} // namespace saber