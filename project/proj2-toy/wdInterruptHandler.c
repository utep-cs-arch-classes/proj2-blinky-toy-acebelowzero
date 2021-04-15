#include <msp430.h>
#include "stateMachines.h"
#include "switches.h"

void
__interrupt_vec(WDT_VECTOR) WDT(){	/* 250 interrupts/sec */
  static char blink_count = 0;
  static char state_count = 0;
  //if (++blink_count == 250) {
    //state_advance();
   // blink_count = 0;
  //}
  //

  
  if (++blink_count == 1) {
    state_advance();
    blink_count = 0;
  }
  if(++state_count == 250) {
    dimChange();
    state_count = 0;
  }
}

