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

#ifndef TEMPERATURE_SERVICE_H
#define TEMPERATURE_SERVICE_H

#include "ble/BLE.h"

/**
* @class TemperatureService
* @brief This service displays the current measured temperature in degrees celcius with a resolution of 0.01, represented as an signed 16bit number.
*/
class TemperatureService {
public:
    /**
     * @param[in] ble
     *               BLE object for the underlying controller.
     * @param[in] temperature
     *               16bit temperature
     */
    BatteryService(BLE &ble, int16_t temperature = 100) :
        _ble(ble),
        _temperature(temperature),
        _temperatureCharacteristic(GattCharacteristic::UUID_TEMPERATURE_CHAR, &_temperature, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY) {

        GattCharacteristic *charTable[] = {&_temperatureCharacteristic};
        GattService temperatureService(GattService::UUID_DEVICE_INFORMATION_SERVICE, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));

        _ble.addService(temperatureService);
    }

    /**
     * @brief Update the battery level with a new value. Valid values lie between 0 and 100,
     * anything outside this range will be ignored.
     *
     * @param temperature
     *              Update the temperature.
     */
    void updateTemperature(int16_t temperature) {
        _temperature = temperature;
        _ble.gattServer().write(_temperatureCharacteristic.getValueHandle(), &_temperature, sizeof(_temperature));
    }

protected:
    /**
     * A reference to the underlying BLE instance that this object is attached to.
     * The services and characteristics will be registered in this BLE instance.
     */
    BLE &_ble;

    uint8_t    _temperature;
    ReadOnlyGattCharacteristic<uint8_t> _temperatureCharacteristic;
};

#endif