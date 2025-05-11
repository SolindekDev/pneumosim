/*
 * PneumoSim - Fast and easy pneumatic circuit simulation
 * Copyright (C) 2023-2024 SolindekDev
 *   
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *   
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *   
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_surface.h>
#include <core/libs.h>
#include <gui/window.h>

#include <pneum/pneumatic_textures.h>
#include <pneum/pneumatic_valve.h>

SDL_Surface* valve_0_ports;
SDL_Surface* valve_2_ports;
SDL_Surface* valve_3_ports;
SDL_Surface* valve_5_ports;

SDL_Surface* valve_2_ports_combination_1;
SDL_Surface* valve_2_ports_combination_2;
SDL_Surface* valve_2_ports_combination_3;

SDL_Surface* valve_3_ports_combination_1;
SDL_Surface* valve_3_ports_combination_2;
SDL_Surface* valve_3_ports_combination_3;
SDL_Surface* valve_3_ports_combination_4;

SDL_Surface* valve_5_ports_combination_1;
SDL_Surface* valve_5_ports_combination_2;
SDL_Surface* valve_5_ports_combination_3;
SDL_Surface* valve_5_ports_combination_4;

SDL_Surface* valve_control_spring;
SDL_Surface* valve_control_lever;
SDL_Surface* valve_control_pedal;
SDL_Surface* valve_control_pneumatic_control;
SDL_Surface* valve_control_push_button;
SDL_Surface* valve_control_roller;
SDL_Surface* valve_control_unidirectional_roller;

int 
pneumatic_textures_load()
{
    valve_0_ports = IMG_Load("res/valve/valve_clean.png");
    valve_2_ports = IMG_Load("res/valve/valve_2_ports.png");
    valve_3_ports = IMG_Load("res/valve/valve_3_ports.png");
    valve_5_ports = IMG_Load("res/valve/valve_5_ports.png");

    valve_control_spring = IMG_Load("res/valve/valve_control/valve_switch_spring.png");
    valve_control_lever = IMG_Load("res/valve/valve_control/valve_switching_lever.png");
    valve_control_pedal = IMG_Load("res/valve/valve_control/valve_switching_pedal.png");
    valve_control_pneumatic_control = IMG_Load("res/valve/valve_control/valve_switching_pneumatic_control.png");
    valve_control_push_button = IMG_Load("res/valve/valve_control/valve_switching_push_button.png");
    valve_control_roller = IMG_Load("res/valve/valve_control/valve_switching_roller.png");
    valve_control_unidirectional_roller = IMG_Load("res/valve/valve_control/valve_switching_unidirectional_roller.png");

    valve_2_ports_combination_1 = IMG_Load("res/valve/valve_combinations/2/combination-1.png");
    valve_2_ports_combination_2 = IMG_Load("res/valve/valve_combinations/2/combination-2.png");
    valve_2_ports_combination_3 = IMG_Load("res/valve/valve_combinations/2/combination-3.png");
    valve_3_ports_combination_1 = IMG_Load("res/valve/valve_combinations/3/combination-1.png");
    valve_3_ports_combination_2 = IMG_Load("res/valve/valve_combinations/3/combination-2.png");
    valve_3_ports_combination_3 = IMG_Load("res/valve/valve_combinations/3/combination-3.png");
    valve_3_ports_combination_4 = IMG_Load("res/valve/valve_combinations/3/combination-4.png");
    valve_5_ports_combination_1 = IMG_Load("res/valve/valve_combinations/5/combination-1.png");
    valve_5_ports_combination_2 = IMG_Load("res/valve/valve_combinations/5/combination-2.png");
    valve_5_ports_combination_3 = IMG_Load("res/valve/valve_combinations/5/combination-3.png");
    valve_5_ports_combination_4 = IMG_Load("res/valve/valve_combinations/5/combination-4.png");

    if (valve_0_ports                       == NULL || 
        valve_2_ports                       == NULL || 
        valve_3_ports                       == NULL || 
        valve_5_ports                       == NULL ||
        valve_2_ports_combination_1         == NULL ||
        valve_2_ports_combination_2         == NULL ||
        valve_2_ports_combination_3         == NULL ||
        valve_3_ports_combination_1         == NULL ||
        valve_3_ports_combination_2         == NULL ||
        valve_3_ports_combination_3         == NULL ||
        valve_3_ports_combination_4         == NULL ||
        valve_5_ports_combination_1         == NULL ||
        valve_5_ports_combination_2         == NULL ||
        valve_5_ports_combination_3         == NULL ||
        valve_5_ports_combination_4         == NULL ||
        valve_control_spring                == NULL ||
        valve_control_lever                 == NULL ||
        valve_control_pedal                 == NULL ||
        valve_control_pneumatic_control     == NULL ||
        valve_control_push_button           == NULL ||
        valve_control_roller                == NULL ||
        valve_control_unidirectional_roller == NULL)
    {
        printf("Failed to load textures: SDL_Error(): %s\n", SDL_GetError());
        return 1;
    }

    return 0;
}

SDL_Surface* 
get_pneumatic_texture_control(int control)
{
    switch (control)
    {
        case CONTROL_NONE:
            return NULL;
            break;
        case CONTROL_SPRING:
            return valve_control_spring;
            break;
        case CONTROL_LEVER:
            return valve_control_lever;
            break;
        case CONTROL_PEDAL:
            return valve_control_pedal;
            break;
        case CONTROL_PNEUMATIC_CONTROL:
            return valve_control_pneumatic_control;
            break;
        case CONTROL_PUSH_BUTTON:
            return valve_control_push_button;
            break;
        case CONTROL_ROLLER:
            return valve_control_roller;
            break;
        case CONTROL_UNIDIRECTIONAL_ROLLER:
            return valve_control_unidirectional_roller;
            break;
        default:
            break;
    }

    return NULL;
}

SDL_Surface*
get_pneumatic_texture_combination(int ports, int combination)
{
    switch (ports)
    {
        case 2:
            if (combination == 1)
                return valve_2_ports_combination_1;
            else if (combination == 2)
                return valve_2_ports_combination_2;
            else if (combination == 3)
                return valve_2_ports_combination_3;
            break;
        case 3:
            if (combination == 1)
                return valve_3_ports_combination_1;
            else if (combination == 2)
                return valve_3_ports_combination_2;
            else if (combination == 3)
                return valve_3_ports_combination_3;
            else if (combination == 4)
                return valve_3_ports_combination_4;
            break;
        case 5:
            if (combination == 1)
                return valve_5_ports_combination_1;
            else if (combination == 2)
                return valve_5_ports_combination_2;
            else if (combination == 3)
                return valve_5_ports_combination_3;
            else if (combination == 4)
                return valve_5_ports_combination_4;
            break;
        default:
            break;
    }

    return NULL;
}

SDL_Surface*
get_pneumatic_texture_valve_blank(int ports)
{
    switch (ports)
    {
        case 0:
            return valve_0_ports;
            break;
        case 2:
            return valve_2_ports;
            break;
        case 3:
            return valve_3_ports;
            break;
        case 5:
            return valve_5_ports;
            break;
        default:
            break;
    }

    return NULL;
}

void 
draw_image_surface(gui_window_t* window, SDL_Surface *surface, vec2_t pos, vec2_t size) 
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    if (!texture) {
        printf("draw_image_surface: SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return;
    }

    SDL_Rect dest_rect = { pos.x, pos.y, size.x, size.y };
    SDL_RenderCopy(window->renderer, texture, NULL, &dest_rect);
    SDL_DestroyTexture(texture);
}

void 
draw_image_surface_horizontal_flip(gui_window_t* window, SDL_Surface *surface, vec2_t pos, vec2_t size) 
{
    SDL_Texture *texture = SDL_CreateTextureFromSurface(window->renderer, surface);
    if (!texture) {
        printf("draw_image_surface: SDL_CreateTextureFromSurface failed: %s", SDL_GetError());
        return;
    }

    SDL_Rect dest_rect = { pos.x, pos.y, size.x, size.y };
    SDL_RenderCopyEx(window->renderer, texture, NULL, &dest_rect, 0, NULL, SDL_FLIP_HORIZONTAL);
    SDL_DestroyTexture(texture);
}