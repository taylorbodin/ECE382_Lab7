#include "sensor.h"

void initMSP430() {

	IFG1=0; 					// clear interrupt flag1
	WDTCTL=WDTPW+WDTHOLD; 		// stop WD

	BCSCTL1 = CALBC1_8MHZ;
	DCOCTL = CALDCO_8MHZ;

	TA0CCR0 = 0x0BA2;							// create a 1mS roll-over period
	TACTL &= ~TAIFG;							// clear flag before enabling interrupts = good practice
	TACTL = ID_3 | TASSEL_2 | MC_1 | TAIE;		// Use 1:8 presclar off MCLK and enable interrupts

	// ADC Subsystem Setup
	ADC10CTL0 = 0;									// Turn off ADC subsystem
	ADC10CTL1 = ADC10DIV_3;						// Channel 4, ADC10CLK/4
	ADC10AE0 = BIT4 | BIT3 | BIT5;		 								// Make P1.4, P1.3, and P1.2 analog inputs
	ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference
	_enable_interrupt();

	return;
}

void selectINCH(int8 inch){

	switch (inch){

	case 5:
		ADC10CTL0 &= ~ENC;
		ADC10CTL1 = INCH_5;
		ADC10CTL0 |= ENC;
		break;

	case 3:
		ADC10CTL0 &= ~ENC;
		ADC10CTL1 = INCH_3;
		ADC10CTL0 |= ENC;
		break;

	case 4:
		ADC10CTL0 &= ~ENC;
		ADC10CTL1 = INCH_4;
		ADC10CTL0 |= ENC;
		break;

	default:
		ADC10CTL0 &= ~ENC;
		ADC10CTL1 = INCH_5;
		ADC10CTL0 |= ENC;
		break;
	}

	return;
}
