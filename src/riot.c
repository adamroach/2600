/* riot.c

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

*/

#include "2600.h"
#include "io.h"
#include "riot.h"

unsigned char timer;
long int interval_counter;
int timer_interval;

unsigned char riot_read(unsigned int address){
  getio();
  switch (address){
    case 0x00: return(joysticks);            /* Joysticks */
    case 0x02: return(console);              /* Console Switches */
    case 0x04: return(timer);                /* Timer read */
    default: return(0);
  }
}

void riot_write(unsigned int address,unsigned char value){
  switch (address){
    case 0x14:
      timer = value; interval_counter = 0;
      timer_interval = 1*3; break;
    case 0x15:
      timer = value; interval_counter = 0;
      timer_interval = 8*3; break;
    case 0x16:
      timer = value; interval_counter = 0;
      timer_interval = 64*3; break;
    case 0x17:
      timer = value; interval_counter = 0;
      timer_interval = 1024*3; break;
  }
}

/* void riot_cycle(unsigned int cycles){
  int i;
  for(i=0; i<cycles; i++){
    interval_counter++;
    if (interval_counter >= timer_interval){
      if (!timer) timer_interval = 3;
      timer--;
      interval_counter = 0L;
    }
  }
} */

/* Okay, here's how it works: every stella cycle, the
   interval_counter needs to be incremented. When it
   reaches the timer_interval, we need to set decrement
   timer and reset interval_counter to zero. As soon
   as the timer reaches zero, we need to reset the
   timer_interval to 3. */

void riot_cycle(unsigned int cycles){
  long int temp;
  interval_counter += cycles;
  temp = interval_counter / timer_interval;
  interval_counter %= timer_interval;
  if(!temp) return;
  if(temp > timer){
    temp = interval_counter;
    temp -= timer * timer_interval;
    timer = 0xff - (temp/3) + 1;
    interval_counter = temp%3;
    timer_interval = 3;
  } else {
    timer -= temp;
  }
}

void init_riot(){
  timer = 0xFF;
  interval_counter = 0;
  timer_interval = 3;
}
