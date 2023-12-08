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
resolution    windowed_res{};
resolution    fullscreen_res{};
resolution    current_res{};

std::set<resolution> resolutions{};

void GLAPIENTRY debug_callback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message,
                               const void* userParam)
{
    printf("OpenGL Debug Message: %s\n", message);
}


void collect_supported_resolutions()
{
    const i32 display_index = SDL_GetWindowDisplayIndex(window);
    const i32 num_modes     = SDL_GetNumDisplayModes(display_index);
    for (i32 i = 0; i < num_modes; ++i)
    {
        SDL_DisplayMode dm;
        SDL_GetDisplayMode(display_index, i, &dm);
        resolutions.insert({ dm.w, dm.h });
    }
}

} // anonymous namespace

bool create(i32 width, i32 height, const char* title, bool fullscreen)
{
    windowed_res.width  = width;
    windowed_res.height = height;

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
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1); // Enable hardware acceleration

    SDL_GL_SetSwapInterval(1); // Enable vsync TODO: Make this a setting

    // TODO: Get settings file, if exists get fullscreen and size settings from it

    current_res = windowed_res;
    window      = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);

    if (!window)
    {
        printf("Failed to create window: %s\n", SDL_GetError());
        return false;
    }

    context = SDL_GL_CreateContext(window);

    if (!context)
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

    collect_supported_resolutions();
    fullscreen_res = *resolutions.rbegin(); // TODO: Get fullscreen resolution from settings file

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(debug_callback, nullptr);

    for (const auto& [w, h] : resolutions)
    {
        printf("Supported resolution: %dx%d\n", w, h);
    }
#endif


    SDL_SetWindowBordered(window, SDL_FALSE);

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

    if (isfullscreen)
    {
        current_res = windowed_res;
        SDL_SetWindowSize(window, windowed_res.width, windowed_res.height);
        SDL_SetWindowFullscreen(window, 0);
    } else
    {
        current_res = fullscreen_res;
        SDL_SetWindowSize(window, fullscreen_res.width, fullscreen_res.height);
        //SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED); // enough for borderless fullscreen?
        SDL_SetWindowFullscreen(window, fsflag); // exclusive fullscreen
    }
    //SDL_ShowCursor(isfullscreen);
}

const std::set<resolution>& supported_resolutions()
{
    return resolutions;
}

resolution current_resolution()
{
    return current_res;
}
i32 width()
{
    return current_res.width;
}
i32 height()
{
    return current_res.height;
}

} // namespace saber::window