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
//  File Name: Scene.cpp
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Scene.h"

#include "Components.h"
#include "Entity.h"
#include "Graphics/Renderer.h"

namespace saber
{

namespace
{
template<typename... T>
void copy_component_if_exists(entity src, entity dest)
{
    (
        [&]() {
            if (src.has_component<T>())
            {
                dest.add_or_replace_component<T>(src.get_component<T>());
            }
        }(),
        ...);
}

template<typename... T>
void copy_component_if_exists(component_group<T...>, entity src, entity dest)
{
    copy_component_if_exists<T...>(src, dest);
}

} // anonymous namespace

entity scene::create_entity()
{
    entity ent{ m_registry.create(), this };
    ent.add_component<transform_component>();

    return ent;
}

void scene::duplicate_entity(entity ent)
{
    const entity new_ent = create_entity();
    copy_component_if_exists(all_components{}, ent, new_ent);
}

void scene::destroy_entity(entity ent)
{
    m_registry.destroy(ent);
}

void scene::on_start() {}
void scene::on_stop() {}

void scene::update(f32 delta)
{
    // TODO: Native script component

    // Physics
}

void scene::render(const camera& cam)
{
    gfx::begin_scene(cam);
    for (const auto group = m_registry.group<transform_component>(entt::get<sprite_component>); const auto ent : group)
    {
        auto [trans, spr] = group.get<transform_component, sprite_component>(ent);
        gfx::draw_sprite(spr.sprite, trans.get_transformation());
    }
    gfx::end_scene();
}

void scene::destroy_all()
{
    m_registry.clear();
}

template<typename T>
void scene::on_component_added(entity ent, T& component)
{
    //static_assert(false);
}

template<>
void scene::on_component_added(entity ent, transform_component& component)
{}

template<>
void scene::on_component_added(entity ent, sprite_component& component)
{}


} // namespace saber