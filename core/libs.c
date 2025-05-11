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
#include <core/message.h>
 
void init_libs()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        PS_ERROR("Failed to initialize SDL: %s", SDL_GetError());

    if (TTF_Init() != 0)
        PS_ERROR("Failed to initialize SDL_ttf: %s", TTF_GetError());

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
        PS_ERROR("Failed to initialize SDL_image: %s", IMG_GetError());

    return;
}