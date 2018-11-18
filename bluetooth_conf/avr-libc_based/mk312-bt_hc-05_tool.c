#include <stdlib.h>
#include "uart.h"
#include "lcd.h"
#include <util/delay.h>

#define WAIT _delay_ms(5000)
#define BTNAME "MK312"
#define PINCODE 1234
#define BAUDRATE 9600

void infinity(void) //don't ask, was fing tired when i wrote this. does the job, and memory is not an issue
{ 
	int i;
	for(i=0;i==1;i=0)
	{ 
		i = 4 ; 
	}
}

int main (void)
{ 
	int i;
	char buffer[16];

	lcd_init(LCD_DISP_ON);
	lcd_puts("init");
//UART INIT
	WAIT;
	for (i = 1; 1 < 11; ++i)
	{
		lcd_clrscr();
		lcd_puts("AT try ");
		itoa(i, buffer, 10);
		lcd_puts(buffer);

		//send AT
		//read everything
		if (buffer[0] == 'O')
		{
			buffer[0] = '\0';
			continue;
		}
		WAIT;
	}
	
	lcd_clrscr();
	if (buffer[0] != '\0')
	{
		lcd_puts("AT error");
		infinity();
	}
	
	//reset
	
    return (0);
}
