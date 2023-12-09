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
//  File Name: Entity.h
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Common.h"
#include "Components.h"

#include "Scene.h"
#include <entt/entt.hpp>

namespace saber
{
class entity
{
public:
    entity() = default;
    entity(entt::entity id, scene* scene) : m_id(id), m_scene(scene) {}

    template<typename T, typename... Args>
    T& add_component(Args&&... args)
    {
        assert(!has_component<T>());
        T& comp = m_scene->m_registry.emplace<T>(m_id, std::forward<Args>(args)...);
        m_scene->on_component_added<T>(*this, comp);
        return comp;
    }

    template<typename T, typename... Args>
    T& add_or_replace_component(Args&&... args)
    {
        T& comp = m_scene->m_registry.emplace_or_replace<T>(m_id, std::forward<Args>(args)...);
        m_scene->on_component_added<T>(*this, comp);
        return comp;
    }

    template<typename T>
    T& get_component()
    {
        assert(has_component<T>());
        return m_scene->m_registry.get<T>(m_id);
    }

    template<typename T>
    bool has_component() const
    {
        if(m_id != entt::null && m_scene->m_registry.valid(m_id))
        {
            return m_scene->m_registry.all_of<T>(m_id);
        }
        return false;
    }

    template<typename T>
    void remove_component() const
    {
        assert(has_component<T>());
        m_scene->m_registry.remove<T>(m_id);
    }

    operator bool() const { return m_id != entt::null; }

    operator entt::entity() const { return m_id; }

    operator u32() const { return (u32) m_id; }

    bool operator==(const entity& other) const { return m_id == other.m_id; }
    bool operator!=(const entity& other) const { return m_id != other.m_id; }


    static entt::registry& registry();

private:
    entt::entity m_id{ entt::null };
    scene*       m_scene{};
};
} // namespace saber