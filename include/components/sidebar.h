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

#ifndef __PS_GUI_COMPONENT_SIDEBAR_H
#define __PS_GUI_COMPONENT_SIDEBAR_H

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

gui_component_t* gui_component_sidebar_create(gui_window_t* window);

#endif /* __PS_GUI_COMPONENT_SIDEBAR_H */