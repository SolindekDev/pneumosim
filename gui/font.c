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

#include <gui/font.h>

#include <core/libs.h>
#include <gui/window.h>
#include <gui/component.h>

#include <SDL2/SDL_ttf.h>

TTF_Font* __small_font;
TTF_Font* __regular_font;
TTF_Font* __bigger_font;

void gui_font_init()
{
    __small_font   = TTF_OpenFont(FONT_PATH, 12);
    __regular_font = TTF_OpenFont(FONT_PATH, 16);
    __bigger_font  = TTF_OpenFont(FONT_PATH, 24);
}

TTF_Font* gui_get_small_font()
{
    return __small_font;
}

TTF_Font* gui_get_regular_font()
{
    return __regular_font;
}

TTF_Font* gui_get_bigger_font()
{
    return __bigger_font;
}

vec2_t gui_font_draw(gui_window_t* win, char* s, TTF_Font* font, vec2_t pos, rgb_color_t color)
{
    SDL_Color color_fg = {CONVERT_TO_SDL_RGB(color)};
    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, s, color_fg, gui_window_get_size_x(win));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);

    vec2_t font_size;
    SDL_QueryTexture(texture, NULL, NULL, &font_size.x, &font_size.y);
    SDL_Rect rect = { pos.x, pos.y, font_size.x, font_size.y };
    SDL_RenderCopy(win->renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return font_size;
}

vec2_t gui_font_get_size(gui_window_t* win, char* s, TTF_Font* font, vec2_t pos)
{
    PS_USE(pos);

    SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, s, (SDL_Color){0,0,0,0}, gui_window_get_size_x(win));
    SDL_Texture *texture = SDL_CreateTextureFromSurface(win->renderer, surface);

    vec2_t font_size;
    SDL_QueryTexture(texture, NULL, NULL, &font_size.x, &font_size.y);
    return font_size;
}