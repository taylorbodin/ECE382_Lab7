#include <msp430g2553.h>

typedef		unsigned char		int8;
typedef		unsigned short		int16;

#define 	LEFT 	1
#define 	CENTER 	2
#define 	RIGHT 	3

#define		DIST_THRESHOLD_L	0x128
#define		DIST_THRESHOLD_R	0x13A
#define		DIST_THRESHOLD_C	0x164
#define		SENSOR_NOISE		0x018	//Average SD of some sensor readings. I've multiplied by 3 to be 99% sure.

void initMSP430();

void selectINCH(int8 inch);
