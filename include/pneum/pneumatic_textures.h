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

#ifndef __PS_PNEUMATIC_TEXTURES_H
#define __PS_PNEUMATIC_TEXTURES_H

#include <core/libs.h>
#include <gui/window.h>

typedef enum {
    CONTROL_NONE = 0,
    CONTROL_SPRING = 1,
    CONTROL_LEVER,
    CONTROL_PEDAL,
    CONTROL_PNEUMATIC_CONTROL,
    CONTROL_PUSH_BUTTON,
    CONTROL_ROLLER,
    CONTROL_UNIDIRECTIONAL_ROLLER
} VALVE_CONTROL;

int pneumatic_textures_load();

SDL_Surface* get_pneumatic_texture_valve_blank(int ports);
SDL_Surface* get_pneumatic_texture_combination(int ports, int combination);
SDL_Surface* get_pneumatic_texture_control(int control);
void draw_image_surface(gui_window_t* window, SDL_Surface *surface, vec2_t pos, vec2_t size);
void draw_image_surface_horizontal_flip(gui_window_t* window, SDL_Surface *surface, vec2_t pos, vec2_t size);

#endif /* __PS_PNEUMATIC_TEXTURES_H */