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
//  File Name: Scene.h
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Common.h"
#include "Graphics/Shader.h"


#include <entt/entt.hpp>

namespace saber
{

class entity;

class scene
{
public:
    scene() = default;
    ~scene() = default;

    entity create_entity();

    void duplicate_entity(entity ent);
    void destroy_entity(entity ent);

    void on_start();
    void on_stop();

    void update(f32 delta);
    void render(const shader& shader);

    void destroy_all();

    template<typename... Components>
    auto get_all_entities()
    {
        return m_registry.view<Components...>();
    }

private:
    template<typename T>
    void on_component_added(entity ent, T& component);

    entt::registry m_registry{};

    friend class entity;
};


}