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
#include "Graphics/Camera.h"
#include "Graphics/Texture.h"

namespace saber::game
{

namespace
{

ref<texture> basictiles{};

void render_quad(const sprite& spr)
{
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    f32 vertices[] = {
        -0.5f, -0.5f, 0.0f, spr.left(), spr.bottom(), // Bottom-left
        0.5f,  -0.5f, 0.0f, spr.right(), spr.bottom(), // Bottom-right
        0.5f,  0.5f, 0.0f, spr.right(), spr.top(), // Top-right
        -0.5f, 0.5f, 0.0f, spr.left(), spr.top(), // Top-left
    };

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*)(3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

void render_quad()
{
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    f32 vertices[] = {
        -100.f, -100.f, 0.0f, 0, 1, // Bottom-left
        100.f,  -100.f, 0.0f, 1, 1, // Bottom-right
        100.f,  100.f,  0.0f, 1, 0,    // Top-right
        -100.f, 100.f,  0.0f, 0, 0,    // Top-left
    };

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(f32), (void*) (3 * sizeof(f32)));
    glEnableVertexAttribArray(1);

    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
}

} // anonymous namespace

void run()
{
    f32 aspect_ratio = (f32) window::width() / (f32) window::height();
    f32 ortho_size = 10.f;
    camera cam{-ortho_size * aspect_ratio, ortho_size * aspect_ratio, -ortho_size, ortho_size};
    shader shader("basic");
    if (!shader.load())
    {
        return;
    }

    basictiles = create_ref<texture>("./assets/sprites/basictiles.png");
    sprite spr(basictiles, 1, 0, 16, 16);

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
        constexpr f32 color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
        shader.set_uniform("uTint", color, 4);
        shader.set_matrix("uProjView", cam.projection_view());
        spr.bind();
        render_quad(spr);

        //basictiles->bind();
        //render_quad();

        window::present();
    }
}
} // namespace saber::game