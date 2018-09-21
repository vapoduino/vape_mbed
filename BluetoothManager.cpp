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
#include "BluetoothManager.h"
#include "ble/BLE.h"

static BatteryService *batteryService = NULL;

// Hackysacky
static int16_t temperature = 0;
static uint8_t power = 0;
static ReadOnlyGattCharacteristic<int16_t> temperatureCharacteristic(GattCharacteristic::UUID_TEMPERATURE_CHAR, &temperature, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ);
static ReadOnlyGattCharacteristic<uint8_t> powerCharacteristics(0xABCD, &power, GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_NOTIFY | GattCharacteristic::BLE_GATT_CHAR_PROPERTIES_READ);
static GattCharacteristic *charTable[] = {&temperatureCharacteristic, &powerCharacteristics};
static GattService temperatureService(0xffff, charTable, sizeof(charTable) / sizeof(GattCharacteristic *));
uint16_t uuid16_list[] = {GattService::UUID_BATTERY_SERVICE, 0xffff};

static void disconnectionCallback(const Gap::DisconnectionCallbackParams_t *params) {
    BLE::Instance().gap().startAdvertising();
}

/**
 * Callback triggered when the ble initialization process has finished
 */
static void bleInitComplete(BLE::InitializationCompleteCallbackContext *params) {
    BLE &ble = params->ble;
    ble_error_t error = params->error;
    Gap& gap = ble.gap();
 
    if (error != BLE_ERROR_NONE) {
        return;
    }
 
    gap.onDisconnection(disconnectionCallback);
 
    batteryService = new BatteryService(ble, 0);
    ble.addService(temperatureService);
 
    /* setup advertising */
    gap.accumulateAdvertisingPayload(GapAdvertisingData::BREDR_NOT_SUPPORTED | GapAdvertisingData::LE_GENERAL_DISCOVERABLE);
    gap.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LOCAL_NAME, (uint8_t *)DEVICE_NAME, sizeof(DEVICE_NAME));
    gap.accumulateAdvertisingPayload(GapAdvertisingData::COMPLETE_LIST_16BIT_SERVICE_IDS, (uint8_t*)uuid16_list, sizeof(uuid16_list));
    gap.setAdvertisingType(GapAdvertisingParams::ADV_CONNECTABLE_UNDIRECTED);
    gap.setAdvertisingInterval(1000); /* 1000ms; in multiples of 0.625ms. */
    gap.startAdvertising();
}

BluetoothManager::BluetoothManager() {
    _batteryManager = new BatteryManager(A3);
    BLE &ble = BLE::Instance(BLE::DEFAULT_INSTANCE);
    ble.init(bleInitComplete);
}

BluetoothManager::~BluetoothManager() {
    free(_batteryManager);
}

void BluetoothManager::bleLoop(float temp) {
    BLE::Instance(BLE::DEFAULT_INSTANCE).waitForEvent(); // this will return upon any system event (such as an interrupt or a ticker wakeup)
 
    batteryService->updateBatteryLevel(_batteryManager->getPercentage());
    temperature = temp * 100;
    uint8_t values[2];
    values[0] = temperature;
    values[1] = temperature >> 8;

    uint8_t power[] = {50};
    BLE::Instance(BLE::DEFAULT_INSTANCE).updateCharacteristicValue(temperatureCharacteristic.getValueHandle(), values, 2);
    BLE::Instance(BLE::DEFAULT_INSTANCE).updateCharacteristicValue(powerCharacteristics.getValueHandle(), power, 1);
}