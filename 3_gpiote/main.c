#include "gpio.h"
#include "gpiote.h"
#include "ppi.h"

int main(){
    // Configure LED Matrix
	for(int i = 17; i <= 20; i++){
		GPIO->DIRSET = (0 << i);
		GPIO->OUTCLR = (0 << i);
	}

    


}