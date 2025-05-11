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

#ifndef __PS_LIBS_H
#define __PS_LIBS_H

#if defined(__MACH__) || defined(__APPLE__)
# define GL_SILENCE_DEPRECATION
#endif /* __MACH__, __APPLE__ */

/* CIMGUI*/
#define CIMGUI_DEFINE_ENUMS_AND_STRUCTS
#define CIMGUI_USE_SDL2
#include "cimgui.h"
#include "cimgui_impl.h"

/* C Headers */
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

/* SDL2 */
#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h> 
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

#ifdef _MSC_VER
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>

#include <core/message.h>

#define __PS_NO_RETURN__ __attribute__((noreturn))

#define PS_NO_NULL(ptr) ({(ptr == NULL)                                                 \
                            ? ps_error(__FILE__, __LINE__, __func__, #ptr " is NULL.")  \
                            : ((void*)0); })
#define PS_TRY(i)       ({ (i == -1)                                                        \
                            ? ps_error(__FILE__, __LINE__, __func__, "\'" #i "\' failed.")  \
                            : ((void*)0); })

#define PS_STRCMP(s1, s2) (strcmp(s1, s2) == 0)

#define PS_USE(v) ((void)(v))

#ifdef IMGUI_HAS_IMSTR
#define igBegin igBegin_Str
#define igSliderFloat igSliderFloat_Str
#define igCheckbox igCheckbox_Str
#define igColorEdit3 igColorEdit3_Str
#define igButton igButton_Str
#endif

#define igGetIO igGetIO_Nil

void init_libs();

#endif /* __PS_LIBS_H */