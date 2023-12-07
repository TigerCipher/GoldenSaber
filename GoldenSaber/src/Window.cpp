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
//  File Name: Window.cpp
//  Date File Created: 12/07/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------

#include "Window.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

namespace saber::window
{

namespace
{
SDL_Window*   window  = nullptr;
SDL_GLContext context = nullptr;
u32           window_width{};
u32           window_height{};
} // anonymous namespace

bool create(u32 width, u32 height, const char* title, bool fullscreen)
{
    window_width  = width;
    window_height = height;

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        printf("Failed to initialize SDL: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window =
        SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, (i32) width, (i32) height, SDL_WINDOW_OPENGL);

    if (window == nullptr)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    context = SDL_GL_CreateContext(window);

    if (context == nullptr)
    {
        printf("Failed to create OpenGL context: %s\n", SDL_GetError());
        return false;
    }

    SDL_GL_MakeCurrent(window, context);

    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        printf("Failed to initialize GLEW\n");
        return false;
    }

    // TODO: Debug callback

    return true;
}
void shutdown()
{
    SDL_GL_DeleteContext(context);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void present()
{
    SDL_GL_SwapWindow(window);
}

void toggle_fullscreen()
{
    constexpr u32 fsflag       = SDL_WINDOW_FULLSCREEN;
    const bool    isfullscreen = SDL_GetWindowFlags(window) & fsflag;
    SDL_SetWindowFullscreen(window, isfullscreen ? 0 : fsflag);
    SDL_ShowCursor(isfullscreen);
}

} // namespace saber::window