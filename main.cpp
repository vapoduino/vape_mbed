#include "mbed.h"
#include "PID.h"

#include "TemperatureSensor.h"

DigitalOut led(P0_1);
Serial serial(P0_13, P0_14);
AnalogIn tempInput(A1);

TemperatureSensor temp(&tempInput, p3);

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

int main() {
	serial.baud(115200);

	adc_init();

	temp.powerUp();

	while (1) {
		led = !led;
		printf("Temperature x 1000: %d \n", (int) (temp.getTemp() * 1000.0f));
		wait_ms(50);
	}
}
