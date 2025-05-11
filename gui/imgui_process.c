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

GLuint texture1, texture2, texture3, texture4;
int w, h;

#define IM_COL32(r, g, b, a) (((ImU32)(a) << 24) | ((ImU32)(b) << 16) | ((ImU32)(g) << 8) | (ImU32)(r))

void imgui_process_init(gui_window_t* window)
{
    GLuint tex = load_texture("res/valve/valve_combinations/2/combination-1.png", &w, &h);
    texture1 = (ImTextureID)(intptr_t)tex;
    texture2 = (ImTextureID)(intptr_t)tex;
    texture3 = (ImTextureID)(intptr_t)tex;
    texture4 = (ImTextureID)(intptr_t)tex;
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

void imgui_process(gui_window_t* window)
{
    if (igBeginTabBar("TabBar", 0)) {
        if (igBeginTabItem("About", NULL, 0)) {
            igText("Valve preview:");
            ImVec2 uv0 = (ImVec2){0.0f, 0.0f};
            ImVec2 uv1 = (ImVec2){1.0f, 1.0f};
            ImVec2 image_size = (ImVec2){(float)w, (float)h};
            igImage(texture1, image_size, uv0, uv1);
            igEndTabItem();
        }
        if (igBeginTabItem("Elements", NULL, 0)) {
            if (igCollapsingHeader_TreeNodeFlags("Air Supplies", 1)) {
                igText("air supply, some other shit");
            }
            if (igCollapsingHeader_TreeNodeFlags("Valves", 0)) {
                const int numColumns = 6; // Number of columns in the grid
                const int numRows = 2;    // Number of rows in the grid
                ImVec2 imageSize = (ImVec2){81, 81}; // Set size of each image (optional)
                igColumns(numColumns, NULL, false); // Create a grid with numColumns columns

                for (int i = 0; i < numRows * numColumns; ++i)
                {
                    // GLuint texture = texture1;
                    // ImVec2 uv0 = (ImVec2){0.0f, 0.0f};
                    // ImVec2 uv1 = (ImVec2){1.0f, 1.0f};
                    // igImage(texture, imageSize, uv0, uv1);

                    // // if ((i + 1) % numColumns != 0)
                    // //     igSameLine(0.0f, 10.0f); 
                    // igNextColumn();
                    GLuint texture = texture1; // Replace with different textures if needed
                    ImVec2 uv0 = (ImVec2){0.0f, 0.0f};
                    ImVec2 uv1 = (ImVec2){1.0f, 1.0f};
                    ImVec4 bg_col = (ImVec4){0, 0, 0, 0};  // Transparent background
                    ImVec4 tint_col = (ImVec4){1, 1, 1, 1}; // No tint (normal color)

                    // Cast texture to ImTextureID safely
                    ImTextureID tex_id = (ImTextureID)(intptr_t)texture;

                    // Unique ID required if using the same texture multiple times
                    char btn_id[32];
                    snprintf(btn_id, sizeof(btn_id), "##imgbtn_%d", i); // Invisible label

                    if (igImageButton(btn_id, tex_id, imageSize, uv0, uv1, bg_col, tint_col)) {
                        // Handle click on this image
                        printf("Image button %d clicked!\n", i);
                    }

                    igNextColumn(); // Move to the next column
                }
                igColumns(1, NULL, false); // Reset columns to default
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
}