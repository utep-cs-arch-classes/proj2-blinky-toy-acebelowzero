#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"


static char dim = 0;



void led_100(){

  red_on = 1;
  green_on =1;
  led_changed = 1;
  led_update();
}

void led_75(){

  static char state = 0;

  int i;

  if(state == 0){

    red_on = 0;
    green_on = 0;
    state = 1;
     led_update();

  } else if(state == 1){
    red_on = 1;
    green_on = 1;
    state = 2;
    led_update();

  } else if(state == 2){
    red_on = 1;
    green_on = 1;
    state = 3;
   led_update();

  } else if(state == 3){
    red_on = 1;
    green_on = 1;
    state = 0;
     led_update();
  }

  led_changed = 1;
   led_update();
}

void led_50(){

  static char state = 0;

  if(state == 0){
    red_on = 0;
    green_on = 0;
    state = 1;
    led_update();

  } else {
    red_on = 1;
    green_on = 1;
    state = 0;
    led_update();
  }
  led_changed = 1;
   led_update();

}

void led_25() {
  static char count = 0;

  if(count == 0) {
    red_on = 0;
    green_on = 1;
    count = 1;
    led_update();
  }
  else if(count == 1) {
    red_on = 0;
    green_on = 0;
    count = 2;
    led_update();
  }
  else if(count == 2) {
    red_on = 1;
    green_on = 1;
    count = 3;
    led_update();
  }
  else if(count == 3) {
    red_on = 1;
    green_on = 1;
    count = 0;
    led_update();
  }
  led_changed = 1;
  led_update();
}

void dimmer() {
  switch(dim) {
    case 0: led_25(); break;
    case 1: led_50(); break;
    case 2: led_75(); break;
  }
  
}

void light_on() {
  red_on = 1;
  green_on =1;
  led_changed = 1;
  led_update();
}

void dimChange (){
  if (dim ==0){
      dim =1;
    }
  else if (dim == 1){
    dim =2;
    // buzzer_set_period(4000);
  }
  else if(dim ==2){
    // buzzer_set_period(5000);
    dim =3;
  }
  else if (dim == 3){
    // buzzer_set_period(4500);
    dim =4;
  }
  else if(dim ==4){
    // buzzer_set_period(3400);
    dim =0;
  }
}

void state_advance()		/* alternate between toggling red & green */
{
  char changed = 0;  
  static char cou = 0;
  static char sta = 0;
  switch(state) {
    // in state 0 by default
    case 1: 
        dimmer(); 
        break;
    case 2:
      green_on = 1;
      red_on = 0;
      changed = 1;
      // buzzer_set_period(1000);
      break;

    case 3:
      light_on();
      changed = 1;
      buzzer_set_period(2000);
      break;
      

    case 4:
      // buzzer_set_period(2000);
      changed = 1;
      break;

  }
  led_changed = changed;
  led_update();
}



