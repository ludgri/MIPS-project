#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"

int getsw(void){
int sw;
PORTD = PORTD >> 8;
//sw = PORTD & 0x000f;
		
return PORTD & 0x000f;
}
int getbtns(void){
int btn;
PORTD = PORTD >> 5;
//btn = PORTD & 0x0007;
return PORTD & 0x0007;
}

