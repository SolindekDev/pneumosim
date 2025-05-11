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
#include "gui/font.h"
#include "gui/manager.h"
#include "pneum/pneumatic_textures.h"
#include "pneum/pneumatic_valve.h"
#include <core/message.h>
#include <imgui_bridge.h>
#include <gui/imgui_process.h>

#include <gui/window.h>

gui_window_t* 
gui_window_create(const char* title, int width, int height)
{
    gui_window_t* window = malloc(sizeof(gui_window_t));
    if (!window) 
    {
        PS_ERROR_NO_EXIT("Failed to allocate memory for GUI window", 0);
        return NULL;
    }

  // Decide GL+GLSL versions
#if __APPLE__
    // GL 3.2 Core + GLSL 150
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG); // Always required on Mac
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
#else
    // GL 3.0 + GLSL 130
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
#endif

    // and prepare OpenGL stuff
    SDL_SetHint(SDL_HINT_RENDER_DRIVER, "opengl");
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_DisplayMode current;
    SDL_GetCurrentDisplayMode(0, &current);

    window->window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                                      width, height, (SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_RESIZABLE));
    if (!window->window) 
    {
        PS_ERROR_NO_EXIT("Failed to create SDL window: %s", SDL_GetError());
        return NULL;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window->window);
    SDL_GL_SetSwapInterval(1);  // enable vsync


    // check opengl version sdl uses
    SDL_Log("opengl version: %s", (char*)glGetString(GL_VERSION));

    // setup imgui
    igCreateContext(NULL);
    
    //set docking
    window->io = igGetIO();
    window->io->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    window->io->ConfigFlags &= ~ImGuiConfigFlags_DockingEnable;           // Enable Docking
    window->io->ConfigFlags &= ~ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    
    ImGui_ImplSDL2_InitBridge((void*)window->window, gl_context);

    igStyleColorsDark(NULL);

    window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED);
    if (!window->renderer) 
    {
        PS_ERROR_NO_EXIT("Failed to create SDL renderer: %s", SDL_GetError());
        return NULL;
    }

    window->font = TTF_OpenFont("res/fonts/Gidole-Regular.ttf", 16);
    if (!window->font)
    {
        PS_ERROR_NO_EXIT("Failed to load font: %s", TTF_GetError());
        return NULL;
    }

    window->quit = false;
    window->title = strdup(title);
    window->frame_state.frame_count = 0;
    window->frame_state.frame_start = SDL_GetTicks();
    window->frame_state.fps = 0;

    window->manager = gui_manager_create(window);
    
    SDL_GetWindowPosition(window->window, &window->window_state.window_x, &window->window_state.window_y);
    return window;
}

void
gui_window_destroy(gui_window_t* window)
{
    TTF_CloseFont(window->font);
    SDL_DestroyRenderer(window->renderer);
    SDL_DestroyWindow(window->window);
    free(window->title);
    free(window);
}

void gui_window_set_title(gui_window_t* window, const char* title)
{
    SDL_SetWindowTitle(window->window, title);
    window->title = strdup(title);
    return;
}

void gui_window_handle_events(gui_window_t* window, SDL_Event event)
{
    ImGui_ImplSDL2_ProcessEventBridge(&event);
    
    switch (event.type)
    {
        case SDL_QUIT:
            window->quit = true;
            break;
        case SDL_WINDOWEVENT:
            switch (event.window.event)
            {
                case SDL_WINDOWEVENT_RESIZED:
                    window->window_state.window_width = event.window.data1;
                    window->window_state.window_height = event.window.data2;
                    break;

                case SDL_WINDOWEVENT_MOVED:
                    window->window_state.window_x = event.window.data1;
                    window->window_state.window_y = event.window.data2;
                    break;

                default:
                    break;
            }
            break;
        default:
            break;
    }

    gui_manager_handle_events(window->manager, &event);
}

int
gui_window_run(gui_window_t* window)
{
    pneumatic_valve_t* valve = create_pneumatic_valve(PNEUMATIC_2_POSITION_VALVE, PNEUMATIC_5_WAY_VALVE);
    valve->current_position = 1;
    set_combination_for_position_valve(valve, 1, 1);
    set_combination_for_position_valve(valve, 2, 2);
    set_controls_for_valve(valve, CONTROL_PUSH_BUTTON, CONTROL_NONE, false, true);
    imgui_process_init(window);
    ImFont* font = ImFontAtlas_AddFontFromFileTTF(window->io->Fonts, "res/fonts/FiraCode-Regular.ttf", 18.0f, NULL, NULL);
    window->io->FontDefault = font;

    gui_font_init();
    while (!window->quit)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
            gui_window_handle_events(window, event);

        int display_w, display_h;
        SDL_GL_GetDrawableSize(window->window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        SDL_SetRenderDrawColor(window->renderer, 18, 18, 18, 255);
        SDL_RenderClear(window->renderer);

        gui_manager_update(window->manager, window->renderer); 
        draw_pneumatic_valve(valve, window, VEC2(100, 100), 1);

        ImGui_ImplSDL2_NewFrameBridge(window->window);
        igNewFrame();
        igPushFont(font);

        igBegin("Tools and settings | Pneumosim", NULL, 0);
        imgui_process(window);

        igPopFont();
        igEnd();
        igRender();
        ImGui_ImplSDL2_RenderBridge(igGetDrawData());
        if (window->io->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            igUpdatePlatformWindows();
            igRenderPlatformWindowsDefault(NULL, NULL);
        }

        SDL_RenderPresent(window->renderer);
    }

    return 0;
}

void gui_window_handle_frames(gui_window_t *window)
{
    window->frame_state.frame_count++;
    if (SDL_GetTicks() - window->frame_state.frame_start >= 1000)
    {
        window->frame_state.fps = window->frame_state.frame_count * 1000 / (SDL_GetTicks() - window->frame_state.frame_start);
        window->frame_state.frame_count = 0;
        window->frame_state.frame_start = SDL_GetTicks();
    }
}

int 
gui_window_get_size_x(gui_window_t* window)
{
    int x;
    SDL_GetWindowSize(window->window, &x, NULL);
    return x;
}

int 
gui_window_get_size_y(gui_window_t* window)
{
    int y;
    SDL_GetWindowSize(window->window, NULL, &y);
    return y;
}

