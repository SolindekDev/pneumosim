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

#define PS_ERROR_MESSAGE                        \
    "\e[0;31mPSCode\e[0m: %s:%d in %s: %s\n"   \

#define PS_ERROR_NO_EXIT_MESSAGE                \
    "\e[0;31mPSCode\e[0m: %s:%d in %s: %s\n"   \

#define PS_SUCCESS_MESSAGE                    \
    "\e[0;32mPSCode\e[0m: %s:%d in %s: %s\n" \

#define PS_FIXME_MESSAGE                                          \
    "\e[0;34mFIXME\e[0m: %s:%d in %s: %s\n" \

void
ps_success(const char* file, int line, 
        const char* func, const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    char* buffer = calloc(512, sizeof(char));
    vsprintf(buffer, msg, ap);

    printf(PS_SUCCESS_MESSAGE, file, line, func, buffer);
    va_end(ap);
    free(buffer);
}

__PS_NO_RETURN__ void 
ps_error(const char* file, int line, 
        const char* func, const char* error, ...)
{
    va_list ap;
    va_start(ap, error);
    char* buffer = calloc(512, sizeof(char));
    vsprintf(buffer, error, ap);

    printf(PS_ERROR_MESSAGE, file, line, func, buffer);
    SDL_Quit();

    va_end(ap);
    exit(1);
}


void 
ps_error_no_exit(const char* file, int line, 
            const char* func, const char* error, ...)
{
    va_list ap;
    va_start(ap, error);
    char* buffer = calloc(512, sizeof(char));
    vsprintf(buffer, error, ap);

    printf(PS_ERROR_NO_EXIT_MESSAGE, file, line, func, buffer);
    va_end(ap);
    free(buffer);
}

void 
ps_fixme(const char* file, int line, 
        const char* func, const char* msg, ...)
{
    va_list ap;
    va_start(ap, msg);
    char* buffer = calloc(512, sizeof(char));
    vsprintf(buffer, msg, ap);

    printf("-------\n");
    printf(PS_FIXME_MESSAGE, file, line, func, buffer);
    printf("-------\n");
    va_end(ap);
    free(buffer); 
}
 