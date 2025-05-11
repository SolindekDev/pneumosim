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

#include "pneum/pneumatic_textures.h"
#include <pneum/pneumatic_valve.h>
#include <gui/window.h>

pneumatic_valve_t* 
create_pneumatic_valve(VALVE_POSITIONS positions, VALVE_PORTS ports)
{
    pneumatic_valve_t* valve = calloc(1, sizeof(pneumatic_valve_t));

    valve->positions = positions;
    valve->ports     = ports;

    return valve;
}

void 
set_combination_for_position_valve(pneumatic_valve_t* valve, int position, int combination)
{
    if (position == 1)
        valve->first_position_combination = combination;
    else if (position == 2)
        valve->second_position_combination = combination;
    else if (position == 3)
        valve->third_position_combination = combination;
}

void 
set_controls_for_valve(pneumatic_valve_t* valve, int left_control, int right_control, bool left_spring, bool right_spring)
{
    valve->left_control  = left_control;
    valve->right_control = right_control;
    valve->left_spring   = left_spring;
    valve->right_spring  = right_spring;
}

void 
draw_pneumatic_valve(pneumatic_valve_t* valve, gui_window_t* window, vec2_t pos, double scale)
{
    for (int i = 0; i < (int)valve->positions; i++)
    {
        SDL_Surface* combination_surface = NULL; 
        if (i == 0)
            combination_surface = get_pneumatic_texture_combination(valve->ports, valve->first_position_combination);
        else if (i == 1)
            combination_surface = get_pneumatic_texture_combination(valve->ports, valve->second_position_combination);
        else if (i == 2)
            combination_surface = get_pneumatic_texture_combination(valve->ports, valve->third_position_combination);
        
        draw_image_surface(window, combination_surface, VEC2(pos.x + ((i * 81) * scale), pos.y + (10 * scale)), VEC2(81 * scale, 81 * scale));
        
        if (i == valve->current_position)
            draw_image_surface(window, get_pneumatic_texture_valve_blank(valve->ports), VEC2(pos.x + (int)((i * 81) * scale), pos.y), VEC2((int)(81 * scale), (int)(101 * scale)));
        else
            draw_image_surface(window, get_pneumatic_texture_valve_blank(0), VEC2(pos.x + (int)((i * 81) * scale), pos.y), VEC2((int)(81 * scale), (int)(101 * scale)));    
    }

    if (valve->left_control != CONTROL_NONE)
        draw_image_surface_horizontal_flip(window, get_pneumatic_texture_control(valve->left_control), VEC2(pos.x - (81 * scale), pos.y + (10 * scale)), VEC2(81 * scale, 81 * scale));
    if (valve->right_control != CONTROL_NONE)
        draw_image_surface(window, get_pneumatic_texture_control(valve->right_control), VEC2(pos.x + ((valve->positions - 1) * 81) + (81 * scale), pos.y + (10 * scale)), VEC2(81 * scale, 81 * scale));

    if (valve->left_spring)
    {
        if (valve->left_control == CONTROL_NONE)
            draw_image_surface_horizontal_flip(window, get_pneumatic_texture_control(CONTROL_SPRING), VEC2(pos.x + ((valve->positions - 1) * 81) + (81 * scale), pos.y + (10 * scale)), VEC2(81 * scale, 81 * scale));
        else
            draw_image_surface_horizontal_flip(window, get_pneumatic_texture_control(CONTROL_SPRING), VEC2(pos.x - (81 * scale), pos.y - (10 * scale)), VEC2(64 * scale, 64 * scale));
    }

    if (valve->right_spring)
    {
        if (valve->left_control == CONTROL_NONE)
            draw_image_surface(window, get_pneumatic_texture_control(CONTROL_SPRING), VEC2(pos.x + ((valve->positions) * (81 * scale)), pos.y + (10 * scale)), VEC2(81 * scale, 81 * scale));
        else
            draw_image_surface(window, get_pneumatic_texture_control(CONTROL_SPRING), VEC2(pos.x + ((valve->positions) * (81 * scale)), pos.y - (10 * scale)), VEC2(64 * scale, 64 * scale));
    }
}