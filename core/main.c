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

#include <components/sidebar.h>

#include <pneum/pneumatic_textures.h>

#include <gui/component.h>
#include <gui/window.h>
#include <gui/manager.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    init_libs();

    gui_window_t* window = gui_window_create("PneumoSim", 1280, 720);
    if (!window)
        return EXIT_FAILURE;

    if (pneumatic_textures_load())
        return EXIT_FAILURE;
    
    return gui_window_run(window);
}