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
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <gui/window.h>

typedef struct __element_menu_t {
    ImTextureID texture_id;
    char* path;
    int   id;
    int   positions; 
    int   ports;
    VALVE_CONTROL left, right;
    int first_combination, second_combination, third_combination;
} element_menu_t;

#define IM_COL32(r, g, b, a) (((ImU32)(a) << 24) | ((ImU32)(b) << 16) | ((ImU32)(g) << 8) | (ImU32)(r))

#define ELEMENT_TEXTURE_WIDTH   573
#define ELEMENT_TEXTURE_HEIGHT  235

int w, h;

element_menu_t elements_valve[] = {
    { 
        .path="res/valve/valve_miniatures/2_2-way-valve-button.png",    
        .id= 1, 
        .positions=2, 
        .ports=2, 
        .left=CONTROL_PUSH_BUTTON, 
        .right=CONTROL_SPRING,
        .first_combination=1,
        .second_combination=2,
        .third_combination=0 
    },
    { 
        .path="res/valve/valve_miniatures/2_2-way-valve-pneumatic.png", 
        .id= 2, 
        .positions=2, 
        .ports=2, 
        .left=CONTROL_PNEUMATIC_CONTROL, 
        .right=CONTROL_SPRING,
        .first_combination=1,
        .second_combination=2,
        .third_combination=0 
    },
    { 
        .path="res/valve/valve_miniatures/3_2-way-valve-button.png",    
        .id= 3, 
        .positions=2, 
        .ports=3, 
        .left=CONTROL_PUSH_BUTTON, 
        .right=CONTROL_SPRING,
        .first_combination=2,
        .second_combination=1,
        .third_combination=0 
    },
    { 
        .path="res/valve/valve_miniatures/3_2-way-valve-pneumatic.png", 
        .id= 4, 
        .positions=2, 
        .ports=3, 
        .left=CONTROL_PNEUMATIC_CONTROL, 
        .right=CONTROL_SPRING,
        .first_combination=2,
        .second_combination=1,
        .third_combination=0 
    },
    { 
        .path="res/valve/valve_miniatures/3_3-way-valve-button.png",    
        .id= 5, 
        .positions=3, 
        .ports=3, 
        .left=CONTROL_PUSH_BUTTON, 
        .right=CONTROL_PUSH_BUTTON,
        .first_combination=2,
        .second_combination=3,
        .third_combination=1 
    },
    { 
        .path="res/valve/valve_miniatures/3_3-way-valve-pneumatic.png", 
        .id= 6, 
        .positions=3, 
        .ports=3, 
        .left=CONTROL_PNEUMATIC_CONTROL, 
        .right=CONTROL_PNEUMATIC_CONTROL,
        .first_combination=2,
        .second_combination=3,
        .third_combination=1 
    },
    { 
        .path="res/valve/valve_miniatures/5_2-way-valve-button.png",    
        .id= 7, 
        .positions=2, 
        .ports=5, 
        .left=CONTROL_PUSH_BUTTON, 
        .right=CONTROL_SPRING,
        .first_combination=2,
        .second_combination=1,
        .third_combination=0 
    },
    { 
        .path="res/valve/valve_miniatures/5_2-way-valve-pneumatic.png", 
        .id= 8, 
        .positions=2, 
        .ports=5, 
        .left=CONTROL_PNEUMATIC_CONTROL, 
        .right=CONTROL_SPRING,
        .first_combination=2,
        .second_combination=1,
        .third_combination=0 
    },
    { 
        .path="res/valve/valve_miniatures/5_3-way-valve-button.png",    
        .id= 9, 
        .positions=3, 
        .ports=5, 
        .left=CONTROL_PUSH_BUTTON, 
        .right=CONTROL_PUSH_BUTTON,
        .first_combination=2,
        .second_combination=3,
        .third_combination=1 
    },
    { 
        .path="res/valve/valve_miniatures/5_3-way-valve-pneumatic.png", 
        .id=10, 
        .positions=3, 
        .ports=5, 
        .left=CONTROL_PNEUMATIC_CONTROL, 
        .right=CONTROL_PNEUMATIC_CONTROL,
        .first_combination=2,
        .second_combination=3,
        .third_combination=1 
    },
};

#define ELEMENTS_VALVE_SIZE (int)(sizeof(elements_valve) / sizeof(element_menu_t))

void imgui_process_init(gui_window_t* window)
{
    for (int i = 0; i < ELEMENTS_VALVE_SIZE; i++)
    {
        GLuint tex = load_texture(elements_valve[i].path, &w, &h);
        elements_valve[i].texture_id = tex;
    }
}

GLuint load_texture(const char* filename, int* out_width, int* out_height) {
    int channels;
    unsigned char* data = stbi_load(filename, out_width, out_height, &channels, STBI_rgb_alpha);
    if (!data) {
        fprintf(stderr, "Failed to load image: %s\n", filename);
        return 0;
    }

    GLuint tex;
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, *out_width, *out_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);
    return tex;
}

pneumatic_valve_t* imgui_process(gui_window_t* window)
{
    pneumatic_valve_t* global_valve = NULL;

    if (igBeginTabBar("TabBar", 0)) {
        if (igBeginTabItem("About", NULL, 0)) {
            igText("Valve preview:");
            igEndTabItem();
        }
        if (igBeginTabItem("Elements", NULL, 0)) {
            if (igCollapsingHeader_TreeNodeFlags("Air Supplies", 1)) {
                igText("air supply, some other shit");
            }
            if (igCollapsingHeader_TreeNodeFlags("Valves", 0)) {
                ImVec2 imageSize = (ImVec2){(w / 2) * (igGetWindowWidth()/1000), (h / 2) * (igGetWindowHeight()/1000)};
                igColumns(3, NULL, false);

                for (int i = 0; i < ELEMENTS_VALVE_SIZE; ++i)
                {
                    if (i > ELEMENTS_VALVE_SIZE)
                        break;

                    GLuint texture = elements_valve[i].texture_id;
                    ImVec2 uv0 = (ImVec2){0.0f, 0.0f};
                    ImVec2 uv1 = (ImVec2){1.0f, 1.0f};
                    ImVec4 bg_col = (ImVec4){0, 0, 0, 0}; 
                    ImVec4 tint_col = (ImVec4){1, 1, 1, 1}; 

                    ImTextureID tex_id = (ImTextureID)(intptr_t)texture;

                    char btn_id[32];
                    snprintf(btn_id, sizeof(btn_id), "##imgbtn_%d", i);

                    if (igImageButton(btn_id, tex_id, imageSize, uv0, uv1, bg_col, tint_col)) {
                            global_valve = create_pneumatic_valve(elements_valve[i].positions, elements_valve[i].ports);
                            if (elements_valve[i].positions == 3)
                                global_valve->current_position = 2;
                            else
                                global_valve->current_position = 1;
                            set_combination_for_position_valve(global_valve, 1, elements_valve[i].first_combination);
                            set_combination_for_position_valve(global_valve, 2, elements_valve[i].second_combination);
                            set_combination_for_position_valve(global_valve, 3, elements_valve[i].third_combination);
                            set_controls_for_valve(global_valve, elements_valve[i].left, elements_valve[i].right, 
                                elements_valve[i].left == CONTROL_SPRING ? true : false, 
                                elements_valve[i].right == CONTROL_SPRING ? true : false); 
                    }

                    igNextColumn(); 
                }
                igColumns(1, NULL, false); 
            }
            if (igCollapsingHeader_TreeNodeFlags("Actuators", 0)) {
                igText("with external return, with spring return");
            }
            if (igCollapsingHeader_TreeNodeFlags("Logic", 0)) {
                igText("koniunkcja i alternatywa");
            }
            if (igCollapsingHeader_TreeNodeFlags("Pressure Control", 0)) {
                igText("pressure regulator");
            }
            if (igCollapsingHeader_TreeNodeFlags("Air Treatment", 0)) {
                igText("lubricator, air filter, drain filter");
            }
            if (igCollapsingHeader_TreeNodeFlags("Other", 0)) {
                igText("pressure gauge");
            }
            igEndTabItem();
        }
        if (igBeginTabItem("Settings", NULL, 0)) {
            igText("Content for Tab 2");
            igEndTabItem();
        }
        igEndTabBar();
    }

    // igText("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / window->io->Framerate, window->io->Framerate);

    return global_valve;
}