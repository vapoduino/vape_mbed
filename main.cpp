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

#include "main.h"

/**
 * Initializes the ADC. Uses one third of the supply voltage as reference and no prescaling for the input.
 */
void adc_init(void) {
	NRF_ADC->ENABLE = ADC_ENABLE_ENABLE_Enabled;
	NRF_ADC->CONFIG &= ~ADC_CONFIG_EXTREFSEL_Msk;
	NRF_ADC->CONFIG &= ~ADC_CONFIG_REFSEL_Msk;
	NRF_ADC->CONFIG &= ~ADC_CONFIG_INPSEL_Msk;
	NRF_ADC->CONFIG |= (ADC_CONFIG_INPSEL_AnalogInputNoPrescaling << ADC_CONFIG_INPSEL_Pos)
			| (ADC_CONFIG_EXTREFSEL_None << ADC_CONFIG_EXTREFSEL_Pos)
			| (ADC_CONFIG_REFSEL_SupplyOneThirdPrescaling << ADC_CONFIG_REFSEL_Pos);
}

/**
 * Called periodically, when the button is pressed.
 */
void heatLoop() {
	if (button.read()) {
		loopTicker.detach();
		serial.printf("Button released\n");
		button.fall(&onButtonPress);
		return;
	}

    controller.setProcessValue(temp.getTemp());

	serial.printf("%d\n", (int) (controller.compute() * 255.0f));
}

/**
 * Called, when the button is pressed. TODO: do not call, when the loopTicker is running.
 */
void onButtonPress() {
	button.fall(0);
	serial.printf("Button pressed\n");

	// TODO: Setup, preheat
	controller.setSetPoint(38.0f); // TODO read desired temperature from settings

	loopTicker.attach(&heatLoop, CICLE_TIME);
}

int main() {
	serial.baud(115200);
	adc_init();
	controller.setInputLimits(0.0f, 230.0f);
	controller.setOutputLimits(0.0, 1.0);
	controller.setBias(0.0f); // TODO: set correct bias.
	controller.setMode(AUTO_MODE);

	button.fall(&onButtonPress);

	while (1) {
		led = !led;
		wait_ms(100);
	}
}
