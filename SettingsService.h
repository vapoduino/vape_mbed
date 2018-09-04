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

#ifndef SETTINGSSERVICE_H
#define SETTINGSSERVICE_H

uint16_t customServiceUUID  = 0xA000; // service UUID
uint16_t readCharUUID       = 0xA001; // read characteristic UUID
uint16_t writeCharUUID      = 0xA002; // write characteristic UUID

//Custom UUID, FFFF is reserved for development
static const uint16_t uuid16_list[] = {0xFFFF};

// Set Up custom Characteristics
static uint8_t readValue[10] ={0};
ReadOnlyArrayGattCharacteristic<uint8_t, sizeof(readValue)> readChar(readCharUUID, readValue);

static uint8_t writeValue[10] = {0};
WriteOnlyArrayGattCharacteristic<uint8_t, sizeof(writeValue)> writeChar(writeCharUUID, writeValue);

GattCharacteristic *characteristics[] = {&readChar, &writeChar};
GattService         customService(customServiceUUID, 
                    characteristics, 
                    sizeof(characteristics) / sizeof(GattCharacteristic *));

void writeCharCallback(BLEDevice ble, const GattCharacteristicWriteCBParams *params) {
    // check to see what characteristic was written, by handle
    if(params->charHandle == writeChar.getValueHandle()) {
        // toggle LED if only 1 byte is written
        if(params->len == 1) {
            led = params->data[0];
            (params->data[0] == 0x00) ? printf("\n\rled on ") :
                        printf("\n\rled off "); // print led toggle
        }
        // print the data if more than 1 byte is written
    else {
        printf("\n\r Data received: length = %d, data = 0x",params->len); 
        for(int x=0; x < params->len; x++) {
            printf("%x",params->data[x]);
        }
    }
    // update the readChar with the value of writeChar
    ble.updateCharacteristicValue(readChar.getValueHandle(), params->data,params->len);
    }
}

#endif
