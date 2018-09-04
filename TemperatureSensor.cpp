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

#include "TemperatureSensor.h"

TemperatureSensor::TemperatureSensor(AnalogIn *analogInput, PinName enablePort) {
	_inputPin = analogInput;
	_enablePort = new DigitalOut(enablePort, 0);

	_values = (uint16_t*) malloc(AVERAGE_COUNT * sizeof(typeof(uint16_t)));
	_counter = 0;
}

void TemperatureSensor::powerUp(void) {
	_enablePort->write(1);
}

void TemperatureSensor::powerDown(void) {
	_enablePort->write(0);
}

float TemperatureSensor::getTemp(void) {
	int value = _inputPin->read_u16();
	float voltage = (value / 1024.0f) * (SUPPLY_VOLTAGE / 3);
	float resistance = SERIES_RECISTANCE / ((SUPPLY_VOLTAGE / voltage) - 1) - WIRE_RESISTANCE;
	float temp = -PT_RESISTANCE * CONST_A
			+ sqrt(PT_RESISTANCE * PT_RESISTANCE * CONST_A * CONST_A
							- 4.0f * PT_RESISTANCE * CONST_B
									* (PT_RESISTANCE - resistance));
	temp /= (2 * PT_RESISTANCE * CONST_B);

	// TODO filtering e.g. with kalman
	return temp;
}
