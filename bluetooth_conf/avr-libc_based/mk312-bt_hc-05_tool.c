/* This is erotic cartoon ware.
 * 
 * If you like it please send one erotic cartoon picture to
 * rpu.bkifft.gbatemp@gmail.com (even if you draw one in paint yourself,
 * everyone likes to draw the cock and balls).
*/

////change to your liking///////////////

#define BTNAME "MK312"
#define PINCODE "1234"

//do not change anything below this line
//////////////////////////////////

#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "uart.h"
#include "lcd.h"

#define WAIT _delay_ms(1000)
#define FLUSH while (!(uart_getc() & UART_NO_DATA)) {}
#define STR_(X) #X
#define STR(X) STR_(X)

void send_uart_cmd(char* command)
{	
	FLUSH;
	uart_puts(command);
	WAIT;
	if (uart_getc() != 'O')
	{
		lcd_puts(command);
		lcd_puts(" error");
		exit(1);
	}
}

int main (void)
{ 
	int i;
	char buffer[16];

	lcd_init(LCD_DISP_ON);
	lcd_puts("init");
    uart_init(UART_BAUD_SELECT(38400,F_CPU)); 
	sei();
	WAIT;
	for (i = 1; 1 < 11; ++i)
	{
		lcd_clrscr();
		lcd_puts("AT try ");
		itoa(i, buffer, 10);
		lcd_puts(buffer);
		
		FLUSH;		
		uart_puts("AT\r\n");
		WAIT;
		buffer[0] = uart_getc();
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
		exit(1);
	}
	
	send_uart_cmd("AT+ORGL\r\n"); //factory defaults
	send_uart_cmd("AT+NAME=" STR(BTNAME) "\r\n"); //name
	send_uart_cmd("AT+UART=19200,0,0\r\n"); //uart settings, 0,0 -> 8N1
	send_uart_cmd("AT+IPSCAN=1024,1,1024,1\r\n"); //increase scan and broadcast interval to save power
	send_uart_cmd("AT+POLAR=1,1\r\n"); //logic high for activity led
	send_uart_cmd("AT+PSWD=" STR(PINCODE) "\r\n"); //pin
	send_uart_cmd("AT+RESET"); //exit config mode by rebooting module
	
	lcd_clrscr();
	lcd_puts("Programming done\n");
	lcd_puts("Sending \"Hello World");
    uart_init(UART_BAUD_SELECT(19200,F_CPU)); 
	while (1)
	{
		uart_puts("Hello world from " STR(BTNAME) "\r\n");
		WAIT;
	}
}
