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

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

gui_component_t* 
gui_component_create(const char* name, int id, int width, int height, int x, int y)
{
    gui_component_t* component = calloc(1, sizeof(gui_component_t));

    component->name = name;
    component->id = id;
    component->width = width;
    component->height = height;
    component->x = x;
    component->y = y;

    return component;
}

void 
gui_component_destroy(gui_component_t* component)
{
    free(component);
}