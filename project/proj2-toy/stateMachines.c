#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


static short freq = 500; // Initial frequency of state 2.
static short state2_status = 1; // Initial state for state 2.

char toggle_red()		/* always toggle! */
{
  static char state = 0;

  switch (state) {
  case 0:
  buzzer_set_period(6000);
    red_on = 1;
    state = 1;
    break;
  case 1:
  buzzer_set_period(500);
    red_on = 0;
    state = 0;
    break;
  }
  return 1;			/* always changes an led */
}

char toggle_green()	/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    buzzer_set_period(200);
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}


void buzzer_stuff() {
  buzzer_set_period(cycles);
}




void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}



