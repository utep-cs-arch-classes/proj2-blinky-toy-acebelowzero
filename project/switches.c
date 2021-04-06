#include <msp430.h>
#include "switches.h"
#include "led.h"

char state_down,  state_change;

static char switch_update_interrupt_sense(){
	char p2val = P2IN;
	PEIES |= (p2val & SWITCHES);
	P2IES &= (p2val & ~SWITCHES);
	return p2val;
}
