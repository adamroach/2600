/* stella.h

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

*/

#define BYTE4 unsigned long int

extern unsigned int stella_rasterline, stella_clock;
extern char framerate, frame; /* in 6507.c */

unsigned char stella_read(unsigned int address);
void stella_write(unsigned int address, unsigned char value);
void stella_cycle(unsigned int numcycles);
void init_stella();
