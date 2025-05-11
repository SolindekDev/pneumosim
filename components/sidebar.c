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
#include <components/sidebar.h>

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

void gui_component_sidebar_update(gui_component_t* component, SDL_Renderer* renderer)
{
    rgb_color_t bg_color = RGB(27, 27, 27);
    rgb_color_t border_color = RGB(39, 39, 39);

    SDL_SetRenderDrawColor(renderer, CONVERT_TO_SDL_RGB(bg_color));
    SDL_Rect rect = { component->x, component->y, component->width, component->height };
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, CONVERT_TO_SDL_RGB(border_color));
    SDL_Rect border_rect = { component->width - 1, component->y, 2, component->height };
    SDL_RenderFillRect(renderer, &border_rect);
}

void gui_component_sidebar_event(gui_component_t* component, SDL_Event* event)
{
    if (event->type == SDL_WINDOWEVENT)
    {
        if (event->window.event == SDL_WINDOWEVENT_RESIZED)
        {
            const int x_size = event->window.data1;
            const int y_size = event->window.data2;
            component->width  = x_size / 3.25;
            component->height = y_size;
        }
    }
}

gui_component_t* gui_component_sidebar_create(gui_window_t* window)
{
    int x_size = gui_window_get_size_x(window);
    int y_size = gui_window_get_size_y(window);

    gui_component_t* sidebar_component = gui_component_create("SIDEBAR", 0, x_size / 3.25, y_size, 0, 0);
    sidebar_component->on_event = &gui_component_sidebar_event;
    printf("%p\n", sidebar_component->on_event);
    sidebar_component->on_update = &gui_component_sidebar_update;
    return sidebar_component;
}