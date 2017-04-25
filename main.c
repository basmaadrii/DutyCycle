//Basma Kadry Osman		3052
//Nouran Kamel El Sekiely 2967

#include <at89c51xd2.h>
#include <stdio.h>
#define dc P1
sbit output = P2^0;
sbit errorLED = P2^6;
sbit SW = P2^7;


unsigned char error, temp, x, xlow, xhigh;
unsigned char TL0_negative, TH0_negative, TL0_positive, TH0_positive;
unsigned int cycles_positive, cycles_negative;
float time_positive, time_negative;

void timer_delay(unsigned char low, unsigned char high);

void main()
{
	SW = 1;					// Initialize SW
	output = 0;			// Initialize output
	TMOD =	0x01;		// Setup Timer 0
	
	while(1)
	{	
		errorLED = 1;		// Turn off LED	when SW is off	
		
		while (SW == 0) //SW is on
		{
			
			//Convert BCD to HEX
			xlow = (dc & 0x0F);
			xhigh = (dc & 0xF0) >> 4;
			x = xhigh * 10 + xlow;
			if (xlow > 9 || xhigh > 9) error = 1;
			else error = 0;
			
			if (!error){
				errorLED = 1;
				
			  //calculate values for TH0 and TL0
				time_positive = (2 * x) / 100.0;		//freq = 500 Hz => period time = 2 ms
				time_negative = 2 - time_positive;
				cycles_positive = (time_positive * 1000) / 0.5425;	//time taken by one cycle = 0.5425
				cycles_negative = (time_negative * 1000) / 0.5425;
				TL0_negative = ((0xFFFF - cycles_negative + 1) & 0x00FF);
				TH0_negative = ((0xFFFF - cycles_negative + 1) & 0xFF00) >> 8;
				TL0_positive = ((0xFFFF - cycles_positive + 1) & 0x00FF);
				TH0_positive = ((0xFFFF - cycles_positive + 1) & 0xFF00) >> 8;
				do{
					temp = dc;
					output = ~output;
					timer_delay(TL0_positive, TH0_positive); //positive portion
					output = ~output;
					timer_delay(TL0_negative, TH0_negative); //negative portion
				} while(dc == temp);
				
			} else {
				output = 0;
				errorLED = 0;
			}
			
		}
	}
}

void timer_delay(unsigned char low, unsigned char high)
{  
	  TH0 = high;
	  TL0 = low;
		TR0 = 1;
	  while(TF0 == 0);
		TR0 = 0;
		TF0 = 0;
}
