// ------------------------------------------------------------------------------
//
// GoldenSaber
//    Copyright 2023 Matthew Rogers
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//        http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.
//
// File Name: Shader
// Date File Created: 12/07/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Common.h"


#include <string>
#include <glm/glm.hpp>

namespace saber
{

class shader
{
public:
    shader(std::string name) : m_name(std::move(name)) {}
    ~shader();

    bool load();

    void bind() const;

    void set_uniform(const std::string& name, const f32* data, u32 count) const;
    void set_matrix(const std::string& name, const glm::mat4& matrix) const;

private:
    u32 m_id{};
    u32 m_vertex_shader{};
    u32 m_fragment_shader{};
    std::string m_name{};
};

} // namespace saber
