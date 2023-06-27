/* riot.h

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

*/

extern unsigned char timer;
extern long int interval_counter;
extern int timer_interval;

unsigned char riot_read(unsigned int address);
void riot_write(unsigned int address,unsigned char value);
void riot_cycle(unsigned int cycles);
void init_riot();
