#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"



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
  buzzer_set_period(500);
}



char state0() {
  char changed = 0;  
  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  led_changed = changed;
  led_update();
}

void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  
  if(v == 2) {
    state = v;
    v=0;
  }
  switch(state) {
    // in state 0 by default
    case 0: 
      buzzer_set_period(0);
      state0();
      break;
      
    // when side button click jump to state 1 then return to state 0 when SW1 is up
    case 1:
      green_on = 1;
      red_on = 0;
      changed = 1;
      buzzer_set_period(1000);
      break;

    case 2:
      buzzer_set_period(5000);
      green_on = 0;
      red_on = 0;
      changed = 1;
      break;
  }
  led_changed = changed;
  led_update();
}



