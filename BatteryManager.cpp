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
#include "BatteryManager.h"

BatteryManager::BatteryManager(PinName batterySensePin) {
    _batteryPin = new AnalogIn(batterySensePin);
}

BatteryManager::~BatteryManager() {
    free(_batteryPin);
}

float BatteryManager::getVoltage() {
    return _batteryPin->read_u16() * VOLTAGE_FACTOR;
}

uint8_t BatteryManager::getPercentage() {
    float difference = getVoltage() - BATTERY_EMPTY_VOLTAGE;

    if (difference < 0) {
        return 0;
    }

    uint8_t percentage = difference / (BATTERY_FULL_VOLTAGE - BATTERY_EMPTY_VOLTAGE) * 100;
    
    if (percentage > 100) {
        return 100;
    }

    return percentage;
}