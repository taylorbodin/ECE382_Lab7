# Prelab

## Useful Information and Implementation plan

The most useful piece of information will come from the lab7.c example code provided by Dr. Couslton. It shows how to 
initialize the ADC subsystem and take readings. My implementation plan will likely be to use the provided code to take some 
measurements at different distances for each sensor. With each sensor characterized I can start to make a library that will 
be easy to implement in lab 8. Finally, I can plot the data from each sensor to achieve A functionality. To take readings
for each sensor I'll just have to add additional ADC inputs. For simplicity sake, I'll convert the sensors one at a time and
just use block logic to poll them. They should update fast enough for my slow robot to avoid crashing into a wall. We're also 
suggested to sample as slowly as possible anyways. 

## Initializing the ADC subsystem

```
ADC10CTL0 = 0;											// Turn off ADC subsystem
		ADC10CTL1 = INCH_4 | ADC10DIV_3 ;						// Channel 4, ADC10CLK/4
		ADC10AE0 = BIT4;		 								// Make P1.4 analog input
		ADC10CTL0 = SREF_0 | ADC10SHT_3 | ADC10ON | ENC;		// Vcc & Vss as reference
```

These are the important registers that I will use in my implementation. I will have to look up how to add more inputs in the
documentation. 

## Hardward interface

I plan on using P1.4, P1.3, and P1.2. These corespond to channel 4, 3, and 2 respectively. 
