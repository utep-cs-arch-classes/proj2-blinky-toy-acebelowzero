#include <msp430.h>
#include "switches.h"
#include "led.h"
#include "stateMachines.h"

char switch_state_down, switch_state_changed; /* effectively boolean */
int state;

static char 
switch_update_interrupt_sense()
{
  char p2val = P2IN;
  /* update switch interrupt to detect changes from current buttons */
  P2IES |= (p2val & SWITCHES);	/* if switch up, sense down */
  P2IES &= (p2val | ~SWITCHES);	/* if switch down, sense up */
  return p2val;
}

void 
switch_init()			/* setup switch */
{  
  P2REN |= SWITCHES;		/* enables resistors for switches */
  P2IE |= SWITCHES;		/* enable interrupts from switches */
  P2OUT |= SWITCHES;		/* pull-ups for switches */
  P2DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  state = 0;
  state_advance();
  
}

void
switch_interrupt_handler()
{
  
  char p2val = switch_update_interrupt_sense();
  

  if((p2val & SW1) == 0) { /* 0 when SW1 is up */
    state = 1;
  }
  else if((p2val & SW2) == 0) {
    state = 2;
  }
  else if((p2val & SW3) == 0) {
    state = 3;
  }
  else if((p2val & SW4) == 0) {
    state = 4;
  }
 
state_advance();
}
