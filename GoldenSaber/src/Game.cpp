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
#include "Scene/Scene.h"
#include "Scene/Entity.h"
#include "Graphics/Renderer.h"

namespace saber::game
{

namespace
{

ref<texture> basictiles{};
ref<texture> characters{};

} // anonymous namespace

void run()
{
    f32           aspect_ratio = (f32) window::width() / (f32) window::height();
    constexpr f32 ortho_size   = 10.f;
    camera        cam{ -ortho_size * aspect_ratio, ortho_size * aspect_ratio, -ortho_size, ortho_size };
    gfx::init();

    basictiles = create_ref<texture>("./assets/sprites/basictiles.png");
    characters = create_ref<texture>("./assets/sprites/characters.png");

    sprite_component spr{};
    //spr.sprite = create_sprite_from_coords(basictiles, {1, 14}, {16, 16});
    spr.sprite = create_sprite_from_coords(basictiles, {1, 0}, {16, 16});

    scene main_scene{};
    //entity ent = main_scene.create_entity();
    //ent.add_component<sprite_component>(spr);

    sprite_component spr2;
    //spr2.sprite   = create_sprite_from_coords(characters, { 0, 7 }, { 16, 16 });
    spr2.sprite   = create_sprite_from_coords(characters, { 3, 1 }, { 16, 16 });
    entity player = main_scene.create_entity();
    player.add_component<sprite_component>(spr2);

    f32 x = -20.f;
    f32 y = -10.f;
    for (u32 i = 0; i < 21; ++i)
    {
        for (u32 j = 0; j < 40; ++j)
        {
            entity ent = main_scene.create_entity();
            ent.add_component<sprite_component>(spr);
            ent.get_component<transform_component>().translation = { x, y };
            x += 1.f;
        }
        x = -20.f;
        y += 1.f;
    }


    //ent.get_component<transform_component>().rotation = glm::radians(45.f);
    //sprite spr(basictiles, 1, 0, 16, 16);

    //quad tile{spr};
    //tile.create();

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
            if (event.type == SDL_WINDOWEVENT)
            {
                if (event.window.event == SDL_WINDOWEVENT_RESIZED)
                {
                    if (window::width() != event.window.data1 || window::height() != event.window.data2)
                    {
                        window::set_resolution({ event.window.data1, event.window.data2 });
                    }

                    aspect_ratio = (f32) window::width() / (f32) window::height();
                    cam.set_projection(-ortho_size * aspect_ratio, ortho_size * aspect_ratio, -ortho_size, ortho_size);
                    glViewport(0, 0, event.window.data1, event.window.data2);
                }
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        constexpr f32 color[4] = { 1.0f, 1.0f, 1.0f, 1.0f };

        main_scene.render(cam);
        //spr.bind();

        //tile.draw();

        //basictiles->bind();
        //render_quad();

        window::present();
    }
}
} // namespace saber::game