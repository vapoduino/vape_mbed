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
#ifndef HEAT_CONTROLLER_H
#define HEAT_CONTROLLER_H

#include "mbed.h"
#include "PinNames.h"

#define PERIOD_TIME 10 // in ms

class HeatController {
public:
    HeatController(PinName outputPin);
    /** Sets the heat. 0.0 means off, 1.0 is full on. */
    void setHeat(float value);
    void stopHeat();
private:
    PwmOut *_gatePin;
};

#endif