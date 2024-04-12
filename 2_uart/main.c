#include "gpio.h"
#include "uart.h"
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>

void button_init()
{
	GPIO->PIN_CNF[13] = (3 << 2); // Setter CC til 11 for å få pull up on pin
	// Fill inn the configuration for the remaining buttons
	GPIO->PIN_CNF[14] = (3 << 2);
}

ssize_t _write(int fd, const void *buf, size_t count)
{
	char *letter = (char *)(buf);
	for (int i = 0; i < count; i++)
	{
		uart_send(*letter);
		letter++;
	}
	return count;
}

int main()
{
	// Configure LED Matrix
	for (int i = 17; i <= 20; i++)
	{
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons -> see button_init()
	button_init();
	uart_init();
	int sleep = 0;
	while (1)
	{

		// Check if button 1 is pressed;
		int val_btn1 = GPIO->IN & (1 << 13);
		if (!val_btn1)
		{
			GPIO->OUT = 1 << 17;
			uart_send('A');
		}

		// Check if button 2 is pressed;
		int val_btn2 = GPIO->IN & (1 << 14);
		if (!val_btn2)
		{
			GPIO->OUT = 1 << 18;
			uart_send('B');
		}

		// Check if something is read
		char letter = uart_read();
		if (letter != '\0')
		{
			GPIO->OUT = 1 << 17 | 1 << 18 | 1 << 19 | 1 << 20;
		}

		int val_btn3 = GPIO->IN & (1 << 15);
		if (!val_btn3)
		{
			iprintf("The average grade in TTK%d was in %d was: %c\n\r", 4235, 2022, 'B');
		}

		sleep = 10000;
		while (--sleep)
			; // Delay
	}
	return 0;
}
