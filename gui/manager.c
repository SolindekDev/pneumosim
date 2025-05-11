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
#include <gui/manager.h>

gui_manager_t* 
gui_manager_create(gui_window_t* window)
{
    gui_manager_t* manager = malloc(sizeof(gui_manager_t));
    if (!manager) 
        PS_ERROR("Failed to allocate memory for GUI manager", 0);

    manager->window = window;
    manager->component_count = 0;

    return manager;
}

void 
gui_manager_destroy(gui_manager_t* manager)
{
    for (int i = 0; i < manager->component_count; i++)
    {
        if (manager->components[i]->on_destroy == NULL)
            manager->components[i]->on_destroy(manager->components[i]);
        free(manager->components[i]);
    }
    manager->component_count = 0;
    free(manager);
}

gui_component_t* 
gui_manager_add_component(gui_manager_t* manager, gui_component_t* component)
{
    if (manager->component_count >= 100)
        PS_ERROR("Maximum number of GUI components reached", 0);

    if (component->on_init != NULL)
        component->on_init(component);
    manager->components[manager->component_count++] = component;
    component->id = manager->component_count - 1;
    return component;
}

void 
gui_manager_remove_component(gui_manager_t* manager, int id)
{
    /* Remove element with the given ID from the array */
    for (int i = id; i < manager->component_count - 1; i++)
        manager->components[i] = manager->components[i + 1];

    manager->component_count--;

    /* Update IDs of remaining components */
    for (int i = id; i < manager->component_count; i++)
        manager->components[i]->id = i;

    /* Call the on_destroy function for the removed component */
    if (manager->components[id]->on_destroy!= NULL)
        manager->components[id]->on_destroy(manager->components[id]);

    free(manager->components[id]);
}

void 
gui_manager_update(gui_manager_t* manager, SDL_Renderer* renderer)
{
    for (int i = 0; i < manager->component_count; i++)
    {
        gui_component_t* component = manager->components[i];
        if (component->on_update != NULL)
            component->on_update(component, renderer);
    }
}

void 
gui_manager_handle_events(gui_manager_t* manager, SDL_Event* event)
{
    for (int i = 0; i < manager->component_count; i++)
    {
        gui_component_t* component = manager->components[i];
        if (component->on_event != NULL)
            component->on_event(component, event);
    }
}

