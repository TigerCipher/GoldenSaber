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
//  File Name: Window.h
//  Date File Created: 12/07/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#pragma once

#include "Types.h"


#include <set>

namespace saber::window
{

struct resolution
{
    i32  width;
    i32  height;
    bool operator<(const resolution& other) const
    {
        return width < other.width || (width == other.width && height < other.height);
    }
};

bool create(i32 width, i32 height, const char* title, bool fullscreen);

void shutdown();

void present();

void toggle_fullscreen();

const std::set<resolution>& supported_resolutions();

resolution current_resolution();

i32 width();
i32 height();

} // namespace saber::window