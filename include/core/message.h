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

#ifndef __PS_MSG_H
#define __PS_MSG_H

#include <core/libs.h>

#define PS_ERROR_NO_EXIT(err, ...) (ps_error_no_exit(__FILE__, __LINE__, __func__, err, __VA_ARGS__))
#define PS_SUCCESS(msg, ...)       (ps_success(__FILE__, __LINE__, __func__, msg, __VA_ARGS__))
#define PS_FIXME(fixme, ...)       (ps_fixme(__FILE__, __LINE__, __func__, fixme, __VA_ARGS__))
#define PS_ERROR(err, ...)         (ps_error(__FILE__, __LINE__, __func__, err, __VA_ARGS__))

void ps_error(const char* file, int line, 
                               const char* func, const char* error, ...);

void ps_error_no_exit(const char* file, int line, 
                    const char* func, const char* error, ...);

void ps_success(const char* file, int line, const char* func, const char* msg, ...);

void ps_fixme(const char* file, int line, const char* func, const char* msg, ...);

#endif /* __PS_MSG_H */