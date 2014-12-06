//-----------------------------------------------------------------
// Name:	Bodin
// File:	main.c
// Date:	Fall 2014
// Purp:	ADC10 readings from sensors to sense distance
//-----------------------------------------------------------------
#include "msp430g2553.h"
#include "sensor.h"


int16 leftDistance;
int16 rightDistance;
int16 centerDistance;
int8 lastSensor;

//----------------------------------------------------------------------
//----------------------------------------------------------------------
int main(void) {

	IFG1=0; 													// clear interrupt flag1
	WDTCTL = WDTPW + WDTHOLD;									// disable WDT

	initMSP430();

	P1DIR = BIT0 | BIT6;

	lastSensor = 4;

	while(1){
		if (rightDistance > 0x0200)	P1OUT |= BIT0;
		if (leftDistance > 0x0200)  P1OUT |= (BIT0 | BIT6);
		if (centerDistance > 0x0200) P1OUT |= BIT6;
		else {
			P1OUT &= ~BIT6;
			P1OUT &= ~BIT0;
		}
	}

} // end main


#pragma vector = TIMER0_A1_VECTOR				// This is from the MSP430G2553.h file
__interrupt void timerOverflow (void) {

	while(ADC10CTL1 & ADC10BUSY);

	switch ( lastSensor ){

	case LEFT:
		leftDistance = ADC10MEM;
    	selectINCH(4);
    	lastSensor = CENTER;
    	break;

	case CENTER:
		rightDistance = ADC10MEM;
    	selectINCH(3);
    	lastSensor = RIGHT;
    	break;

	case RIGHT:
		centerDistance = ADC10MEM;
		selectINCH(5);
		lastSensor = LEFT;
		break;

	default:
		selectINCH(5);
		ADC10CTL0 |= ADC10SC;
		lastSensor = CENTER;
		break;
	}

		ADC10CTL0 |= ADC10SC;

	    TACTL &= ~TAIFG;
}
