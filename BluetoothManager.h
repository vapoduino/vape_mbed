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
#ifndef BLUETOOTH_MANAGER_H
#define BLUETOOTH_MANAGER_H

#include "BLE.h"
#include "BatteryService.h"
#include "BatteryManager.h"

static const char DEVICE_NAME[] = "Vape";

class BluetoothManager {
public:
    BluetoothManager();
    virtual ~BluetoothManager();
    /** 
     * Handles bluetooth events. Should be called in the main loop.
     */
    void bleLoop(float temp);
private:
    BatteryManager *_batteryManager;
};

#endif