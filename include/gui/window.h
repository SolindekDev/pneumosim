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

#ifndef __PS_GUI_WINDOW_H
#define __PS_GUI_WINDOW_H

#include <core/libs.h>

typedef struct __gui_manager_t gui_manager_t;
 
/* 
 * Define the structure for the GUI window. This structure will be used to
 * represent the GUI window and its state. The structure will be initialized
 * with default values in gui_window_create().
 */
typedef struct __gui_window_t {
    SDL_Window* window;
    SDL_Renderer* renderer;
    TTF_Font* font;
    bool quit;
    char* title;
    ImGuiIO* io;

    union {
        int frame_count;
        Uint32 frame_start;
        int fps;
    } frame_state;

    union {
        int mouse_x;
        int mouse_y;
        bool mouse_left_down;
        bool mouse_right_down;
    } mouse_state;

    union {
        int window_width;
        int window_height;
        int window_x;
        int window_y;
    } window_state;

    gui_manager_t* manager;

    /* Function prototypes */
    void (*on_update)(struct __gui_window_t* window);
    void (*on_render)(struct __gui_window_t* window);
    void (*on_mouse_motion)(struct __gui_window_t* window, int x, int y);
    void (*on_mouse_button_down)(struct __gui_window_t* window, int button, int x, int y);
    void (*on_mouse_button_up)(struct __gui_window_t* window, int button, int x, int y);
} gui_window_t;

typedef struct __vec2_t {
    int x, y;
} vec2_t;

typedef struct __rgb_color_t {
    unsigned char r,g,b,a;
} rgb_color_t;

#define RGBA(r, g, b, a) ((rgb_color_t) {r, g, b, a})
#define RGB(r, g, b) ((rgb_color_t) {r, g, b, 255})
#define VEC2(x,y) ((vec2_t) {x,y})

#define CONVERT_TO_SDL_RGB(cl) cl.r, cl.g, cl.b, cl.a

gui_window_t* gui_window_create(const char* title, int width, int height);
void gui_window_destroy(gui_window_t* window);
int  gui_window_run(gui_window_t *window);
void gui_window_handle_frames(gui_window_t *window);
void gui_window_set_title(gui_window_t* window, const char* title);
void gui_window_handle_events(gui_window_t* window, SDL_Event event);

int gui_window_get_size_x(gui_window_t* window);
int gui_window_get_size_y(gui_window_t* window);

#endif /* __PS_GUI_WINDOW_H */