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

#ifndef __PS_GUI_COMPONENT_H
#define __PS_GUI_COMPONENT_H

#include <core/libs.h>
#include <gui/window.h>

/* 
 * This structure represents a graphical component in the GUI. The structure will be
 * used to represent the graphical components of buttons, sliders, etc. The structure will be
 * initialized with default values in gui_component_create().
 */
typedef struct __gui_component_t {
    const char* name;
    int id;

    int width, height;
    int x, y;

    bool is_active;
    bool is_highlighted;
    bool is_pressed;

    /* TODO */
    void (*on_mouse_enter)(struct __gui_component_t* component);
    void (*on_mouse_leave)(struct __gui_component_t* component);
    void (*on_mouse_click)(struct __gui_component_t* component);
    
    void (*on_update)(struct __gui_component_t* component, SDL_Renderer* renderer);
    void (*on_destroy)(struct __gui_component_t* component);
    void (*on_init)(struct __gui_component_t* component);
    void (*on_event)(struct __gui_component_t* component, SDL_Event* event);
} gui_component_t;

gui_component_t* gui_component_create(const char* name, int id, int width, int height, int x, int y);
void gui_component_destroy(gui_component_t* component);

#endif /* __PS_GUI_COMPONENT_H */