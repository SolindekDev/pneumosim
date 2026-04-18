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

#include <SDL2/SDL_events.h>
#include <components/workspace.h>

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

void gui_component_workspace_update(gui_component_t* component, SDL_Renderer* renderer)
{
    
}

void gui_component_workspace_event(gui_component_t* component, SDL_Event* event)
{

}

gui_component_t* gui_component_workspace_create(gui_window_t* window)
{
    int x_size = gui_window_get_size_x(window);
    int y_size = gui_window_get_size_y(window);

    // -1 on the size means this component will be full the size of a full window.
    gui_component_t* sidebar_component = gui_component_create("WORKSPACE", 1, -1, -1, 0, 0);
    sidebar_component->on_event = &gui_component_sidebar_event;
    sidebar_component->on_update = &gui_component_sidebar_update;
    return sidebar_component;
}