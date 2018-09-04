/*
 * Created 03. Dec 2017 - TemperatureSensor.h
 * 
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

#include "mbed.h"
#include "PinNames.h"

#ifndef TEMPERATURESENSOR_H
#define TEMPERATURESENSOR_H

#define PT_RESISTANCE 100.0f
#define SERIES_RECISTANCE 510.0f
#define SUPPLY_VOLTAGE 3.18f
#define WIRE_RESISTANCE 1.8f

#define CONST_A 0.00390830f
#define CONST_B -0.0000005775f
#define CONST_C -0.00000000000418301f

#define AVERAGE_COUNT 10

class TemperatureSensor {
public:
	TemperatureSensor(AnalogIn *analogInput, PinName enablePort);
	void powerUp(void);
	void powerDown(void);
	float getTemp(void);
private:
	AnalogIn *_inputPin;
	DigitalOut *_enablePort;
    uint16_t *_values;
    uint16_t _counter;
};

#endif
