/*
 * This file is part of the vape_mbed distribution (https://github.com/acidg/vape_mbed)
 * Copyright (C) 2018 acidg
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef MAIN_H
#define MAIN_H

#include "mbed.h"
#include "PID.h"

#include "TemperatureSensor.h"

#define CICLE_TIME 0.1f // in seconds
#define PID_P 1.0f
#define PID_I 0.0f
#define PID_D 0.0f

DigitalOut led(P0_1);
AnalogIn tempInput(A1);
InterruptIn button(P0_10, PullUp);
PID controller(PID_P, PID_I, PID_D, CICLE_TIME);
Ticker loopTicker;

Serial serial(P0_13, P0_14);
TemperatureSensor temp(&tempInput, P0_3);

void heatLoop();
void onButtonPress();

int main();

#endif