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
// File Name: Components
// Date File Created: 12/09/2023
// Author: Matt
//
// ------------------------------------------------------------------------------
#pragma once

#include "Common.h"
#include "Graphics/Texture.h"


#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

namespace saber
{

struct transform_component
{
    glm::vec2 translation{};
    glm::vec2 scale{ 1.0f, 1.0f };
    f32       rotation{};

    glm::mat4 get_transformation() const
    {
        const glm::mat4 rot = glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        return glm::translate(glm::mat4(1.0f), glm::vec3(translation, 1.0f)) * rot * glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));
    }
};

struct sprite_component
{
    ref<sprite> sprite;
};



template<typename... T>
struct component_group {};

using all_components = component_group<transform_component, sprite_component>;

} // namespace saber
