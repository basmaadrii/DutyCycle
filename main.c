#include <at89c51xd2.h>
#include <stdio.h>
sbit output = P2^0;
sbit errorLED = P2^6;
sbit SW = P2^7;
void timer_delay(unsigned char low, unsigned char high);
void main()
{
	SW = 1;					// Initialize SW
	output = 0;			// Initialize output
	TMOD =	0x01;		// Setup Timer 0
	while( 1 )
	{	
		errorLED = 1;		// Turn off LED		
		while (SW == 0)
		{
			unsigned char x = P1;
			switch(x)
			{
				case 0x20:
					errorLED = 1;
					output = ~output;
					timer_delay(0x1F, 0xFD);
					output = ~output;
					timer_delay(0x7B, 0xF4);
					break;
				
				case 0x25:
					errorLED = 1;
					output = ~output;
					timer_delay(0x66, 0xFC);
					output = ~output;
					timer_delay(0x33, 0xf5);
					break;
				
				case 0x50:
					errorLED = 1;
					output = ~output;
					timer_delay(0xCD, 0xF8);
					output = ~output;
					timer_delay(0xCD, 0xF8);
					break;
				
				case 0x75:
					errorLED = 1;
					output = ~output;
					timer_delay(0x33, 0xf5);
					output = ~output;
					timer_delay(0x66, 0xFC);
					break;
				
				case 0x80:
					errorLED = 1;
					output = ~output;
					timer_delay(0x7B, 0xF4);
					output = ~output;
					timer_delay(0x1F, 0xFD);
					break;
				
				default:
					errorLED = 0;
					output = 0;
					break;
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