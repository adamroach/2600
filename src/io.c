/* io.c

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

  Sloppy but fast interface to the input hardware.
  The values are passed via global variables to cut down
  on overhead.

*/

#include <stdlib.h>
#include "2600.h"
#include "graphics.h"

unsigned char console   = 0xFF;
unsigned char joysticks = 0xFF;
unsigned fire1          = 0xFF;
unsigned fire2          = 0xFF;
unsigned char pot1      = 0x00;
unsigned char pot2      = 0x00;
unsigned char pot3      = 0x00;
unsigned char pot4      = 0x00;

void init_io(){
}

void reset_io(){
}

void getio(){
  unsigned char key, lastkey;
  lastkey = key^1;
  while(key != lastkey){
    lastkey=key;
    key=0; /* read a key here */
    switch(key){
      case 0x3B: console &= 0xF7; break; /* F1 = B&W */
      case 0x3C: console |= 0x08; break; /* F2 = Color */
      case 0x0F: console &= 0xFD; break; /* TAB = select */
      case 0x8F: console |= 0x02; break;
      case 0x01: console &= 0xFE; break; /* Esc = reset */
      case 0x81: console |= 0x01; break;
      case 0x4D: joysticks &= 0xF7; break; /* P1 right */
      case 0xCD: joysticks |= 0x08; break;
      case 0x4B: joysticks &= 0xFB; break; /* P1 left  */
      case 0xCB: joysticks |= 0x04; break;
      case 0x50: joysticks &= 0xFD; break; /* P1 down  */
      case 0xD0: joysticks |= 0x02; break;
      case 0x48: joysticks &= 0xFE; break; /* P1 up    */
      case 0x52: fire2 = 0x00; break;
      case 0xD2: fire2 = 0xFF; break;
      case 0xC8: joysticks |= 0x01; break;
      case 0x20: joysticks &= 0x7F; break; /* P0 right */
      case 0xA0: joysticks |= 0x80; break;
      case 0x1E: joysticks &= 0xBF; break; /* P0 left  */
      case 0x9E: joysticks |= 0x40; break;
      case 0x2D: joysticks &= 0xDF; break; /* P0 down  */
      case 0xAD: joysticks |= 0x20; break;
      case 0x11: joysticks &= 0xEF; break; /* P0 up    */
      case 0x91: joysticks |= 0x10; break;
      case 0x39: fire1 = 0x00; break;
      case 0xB9: fire1 = 0xFF; break;
      case 0x10: reset_io(); reset_screen(); exit(0);   /* q exits */
    }
  }
}
