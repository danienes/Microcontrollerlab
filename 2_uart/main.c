#include "gpio.h"
#include "uart.h"


void button_init(){ 
	GPIO->PIN_CNF[13] = (3 << 2); //Setter CC til 11 for å få pull up on pin
	// Fill inn the configuration for the remaining buttons 
	GPIO->PIN_CNF[14] = (3 << 2);
}

int main(){
	// Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (1 << i);
		GPIO->OUTCLR = (1 << i);
	}

	// Configure buttons -> see button_init()
	button_init();

	int sleep = 0;
	while(1){

		/* Check if button 1 is pressed; */
		int val_btn1 = GPIO->IN & (1<<13);
		if (!val_btn1)
		{
            GPIO->OUT = 1<<17;
			uart_send('A');
            
		}
		

		/* Check if button 2 is pressed; */
		int val_btn2 = GPIO->IN & (1<<14);
		if (!val_btn2)
		{
            GPIO->OUT = 1<<18;
			uart_send('B');
		}

		sleep = 10000;
		while(--sleep); // Delay
	}
	return 0;
}

