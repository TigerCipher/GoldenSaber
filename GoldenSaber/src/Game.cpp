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
//  File Name: Game.cpp
//  Date File Created: 12/07/2023
//  Author: Matt
//
//  ------------------------------------------------------------------------------
#include "Game.h"

#include "Window.h"

#include <SDL2/SDL.h>
#include <GL/glew.h>

#include "Graphics/Shader.h"

namespace saber::game
{

namespace
{

void render_quad()
{
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    f32 vertices[] = {
        -0.5f, -0.5f, 0.0f, // Bottom-left
        0.5f,  -0.5f, 0.0f, // Bottom-right
        0.5f,  0.5f, 0.0f, // Top-right
        -0.5f, 0.5f, 0.0f // Top-left
    };

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

} // anonymous namespace

void run()
{
    shader shader("basic");
    if (!shader.load())
    {
        return;
    }

    bool running = true;
    while (running)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    running = false;
                }
                if (event.key.keysym.sym == SDLK_f)
                {
                    window::toggle_fullscreen();
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.bind();
        constexpr f32 color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
        shader.set_uniform("uTint", color, 4);

        render_quad();

        window::present();
    }
}
} // namespace saber::game