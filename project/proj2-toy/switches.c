#include <msp430.h>
#include "switches.h"
#include "led.h"


char switch_state_down, switch_state_changed; /* effectively boolean */
int state, v=1;

static char 
switch_update_interrupt_sense()
{
  char p1val = P1IN;
  /* update switch interrupt to detect changes from current buttons */
  P1IES |= (p1val & SWITCHES);	/* if switch up, sense down */
  P1IES &= (p1val | ~SWITCHES);	/* if switch down, sense up */
  return p1val;
}

void 
switch_init()			/* setup switch */
{  
  P1REN |= SWITCHES;		/* enables resistors for switches */
  P1IE |= SWITCHES;		/* enable interrupts from switches */
  P1OUT |= SWITCHES;		/* pull-ups for switches */
  P1DIR &= ~SWITCHES;		/* set switches' bits for input */
  switch_update_interrupt_sense();
  led_update();
}

void
switch_interrupt_handler()
{
  
  char p1val = switch_update_interrupt_sense();

  switch_state_down = (p1val & SW1) ? 0 : 1; /* 0 when SW1 is up */
  // TODO: ADD OTHER SWITCHES
  
  // TODO ADD OTHER SWITCES
  if(switch_state_down) {
    state = 1;
    v = v+1;
    
  }else {
    state = 0;
  }
  state_advance();
}
