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

#ifndef __PS_GUI_FONT_H
#define __PS_GUI_FONT_H

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

#define FONT_PATH "res/fonts/Gidole-Regular.ttf"

void gui_font_init();

TTF_Font* gui_get_small_font();
TTF_Font* gui_get_regular_font();
TTF_Font* gui_get_bigger_font();

vec2_t gui_font_draw(gui_window_t* win, char* s, TTF_Font* font, vec2_t pos, rgb_color_t color);
vec2_t gui_font_get_size(gui_window_t* win, char* s, TTF_Font* font, vec2_t pos);

#endif /* __PS_GUI_FONT_H */