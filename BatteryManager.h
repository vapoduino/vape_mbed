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
#ifndef BATTERY_MANAGER_H
#define BATTERY_MANAGER_H

#include "mbed.h"

#define VOLTAGE_FACTOR 0.006358399 // V/bit
#define BATTERY_FULL_VOLTAGE 4.15
#define BATTERY_EMPTY_VOLTAGE 3.7

class BatteryManager {
public:
    BatteryManager(PinName batterySensePin);
    virtual ~BatteryManager();
    float getVoltage();
    uint8_t getPercentage();
private:
    AnalogIn *_batteryPin;
};

#endif