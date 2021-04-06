#include <msp430.h>
#include "libTimer.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

void main(){
	configureClocks();
	enableWDTInterrupts();
}
