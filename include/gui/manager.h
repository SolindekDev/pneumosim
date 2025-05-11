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

#ifndef __PS_GUI_MANAGER_H
#define __PS_GUI_MANAGER_H

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

typedef struct __gui_manager_t {
    gui_window_t* window;
    gui_component_t* components[100];
    int component_count;
} gui_manager_t;

gui_manager_t* gui_manager_create(gui_window_t* window);
void gui_manager_destroy(gui_manager_t* manager);

gui_component_t* gui_manager_add_component(gui_manager_t* manager, gui_component_t* component);
void gui_manager_remove_component(gui_manager_t* manager, int id);

void gui_manager_update(gui_manager_t* manager, SDL_Renderer* renderer);
void gui_manager_handle_events(gui_manager_t* manager, SDL_Event* event);
void gui_manager_on_init(gui_manager_t* manager);

#endif /* __PS_GUI_MANAGER_H */