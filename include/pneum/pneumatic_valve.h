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

#ifndef __PS_PNEUMATIC_VALVE_H
#define __PS_PNEUMATIC_VALVE_H

#include <gui/window.h>

typedef enum VALVE_PORTS {
    PNEUMATIC_2_WAY_VALVE = 2,
    PNEUMATIC_3_WAY_VALVE = 3,
    PNEUMATIC_5_WAY_VALVE = 5
} VALVE_PORTS;

typedef enum VALVE_POSITIONS {
    PNEUMATIC_2_POSITION_VALVE = 2,
    PNEUMATIC_3_POSITION_VALVE = 3,
} VALVE_POSITIONS;

typedef struct __pneumatic_valve_t {
    VALVE_POSITIONS positions;
    VALVE_PORTS     ports;

    int current_position;

    int first_position_combination;
    int second_position_combination;
    int third_position_combination;

    int left_control;
    int right_control;

    bool left_spring;
    bool right_spring;
} pneumatic_valve_t;

pneumatic_valve_t* create_pneumatic_valve(VALVE_POSITIONS positions, VALVE_PORTS ports);
void set_combination_for_position_valve(pneumatic_valve_t* valve, int position, int combination);
void set_controls_for_valve(pneumatic_valve_t* valve, int left_control, int right_control, bool left_spring, bool right_spring);

void draw_pneumatic_valve(pneumatic_valve_t* valve, gui_window_t* window, vec2_t pos, double scale);

#endif /* __PS_PNEUMATIC_VALVE_H */