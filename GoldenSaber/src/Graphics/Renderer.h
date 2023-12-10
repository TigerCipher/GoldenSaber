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
//  File Name: Renderer.h
//  Date File Created: 12/09/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Common.h"

#include "Camera.h"

#include "Texture.h"

namespace saber::gfx
{

void init();
void shutdown();

void begin_scene(const camera& cam);
void end_scene();

void draw_sprite(const ref<sprite>& spr, const glm::mat4& transform, const glm::vec4& tint_color = {1.f, 1.f, 1.f, 1.f});
}