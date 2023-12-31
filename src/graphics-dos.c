/* graphics.c

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

*/

#include "2600.h"

char colormap[256][3]={{0,0,0},{18,18,18},{21,21,21},{24,24,24},{27,27,27},
                       {31,31,31},{34,34,34},{37,37,37},{40,40,40},{43,43,43},
                       {47,47,47},{50,50,50},{53,53,53},{56,56,56},{59,59,59},
                       {63,63,63},{25,25, 0},{27,27, 0},{29,29, 0},{32,32, 0},
                       {34,34, 0},{37,37, 0},{40,40, 0},{42,42, 0},{44,44, 0},
                       {47,47, 0},{50,50, 0},{52,52, 0},{55,55, 0},{57,57, 0},
                       {59,59, 0},{63,63, 0},{29,17, 0},{31,17, 0},{33,18, 0},
                       {35,20, 0},{37,21, 0},{40,23, 0},{42,24, 0},{44,26, 0},
                       {46,26, 0},{48,28, 0},{51,29, 0},{53,31, 0},{55,32, 0},
                       {57,34, 0},{59,35, 0},{63,37, 1},{26, 9, 0},{28, 9, 0},
                       {30,10, 0},{32,11, 0},{35,12, 0},{38,14, 0},{40,14, 0},
                       {42,15, 0},{45,16, 0},{47,17, 0},{50,19, 0},{52,19, 0},
                       {55,20, 0},{57,21, 0},{59,22, 0},{63,24, 1},{29,16,16},
                       {31,16,16},{33,17,17},{35,19,19},{37,20,20},{40,22,21},
                       {42,23,23},{44,24,24},{46,26,25},{48,27,27},{51,29,28},
                       {53,30,29},{55,31,31},{57,33,32},{59,34,33},{63,36,35},
                       {24, 2,23},{26, 1,25},{28, 1,27},{31, 1,30},{33, 1,32},
                       {37, 2,36},{39, 2,38},{41, 2,41},{44, 1,43},{46, 1,46},
                       {50, 2,49},{52, 2,52},{54, 2,54},{57, 2,57},{59, 2,59},
                       {63, 3,63},{23, 2,26},{24, 1,28},{25, 1,30},{28, 1,32},
                       {29, 1,35},{31, 2,37},{33, 2,39},{35, 2,41},{36, 1,44},
                       {39, 1,46},{40, 2,48},{42, 2,50},{44, 2,53},{46, 2,55},
                       {47, 2,57},{50, 3,61},{ 4, 2,28},{ 3, 1,30},{ 3, 1,32},
                       { 3, 1,34},{ 2, 1,36},{ 2, 1,39},{ 2, 1,41},{ 2, 1,43},
                       { 1, 0,46},{ 1, 0,48},{ 1, 0,51},{ 1, 0,53},{ 0, 0,55},
                       { 0, 0,57},{ 0, 0,59},{ 0, 0,63},{ 4, 2,28},{ 3, 1,30},
                       { 3, 1,32},{ 3, 1,34},{ 2, 1,36},{ 2, 1,39},{ 2, 1,41},
                       { 2, 1,43},{ 1, 0,46},{ 1, 0,48},{ 1, 0,51},{ 1, 0,53},
                       { 0, 0,55},{ 0, 0,57},{ 0, 0,59},{ 0, 0,63},{19,16,25},
                       {19,16,27},{21,18,29},{23,20,32},{23,21,34},{25,23,37},
                       {27,25,40},{29,27,42},{29,28,44},{31,30,47},{33,32,50},
                       {35,34,52},{35,35,55},{37,37,57},{39,39,59},{41,41,63},
                       { 8,20,21},{ 7,22,23},{ 6,25,26},{ 6,28,28},{ 5,30,31},
                       { 5,34,34},{ 4,37,36},{ 4,39,39},{ 3,42,42},{ 3,45,45},
                       { 2,48,48},{ 2,51,50},{ 1,54,53},{ 1,56,55},{ 0,59,58},
                       { 0,63,62},{ 0,21,15},{ 0,23,17},{ 0,26,19},{ 0,28,21},
                       { 0,31,23},{ 0,35,25},{ 0,37,27},{ 0,40,29},{ 0,42,31},
                       { 0,45,33},{ 0,49,35},{ 0,51,37},{ 0,54,39},{ 0,56,41},
                       { 0,59,43},{ 0,63,46},{ 0,21, 0},{ 0,23, 0},{ 0,26, 0},
                       { 0,28, 0},{ 0,31, 0},{ 0,35, 0},{ 0,37, 0},{ 0,40, 0},
                       { 0,42, 0},{ 0,45, 0},{ 0,49, 0},{ 0,51, 0},{ 0,54, 0},
                       { 0,56, 0},{ 0,59, 0},{ 0,63, 0},{17,21, 0},{18,23, 0},
                       {20,26, 0},{23,28, 0},{25,31, 0},{28,35, 0},{30,37, 0},
                       {33,40, 0},{34,42, 0},{37,45, 0},{39,49, 0},{42,51, 0},
                       {44,54, 0},{47,56, 0},{49,59, 0},{52,63, 0},{25,21, 0},
                       {27,22, 0},{29,25, 0},{32,26, 0},{34,29, 0},{37,32, 0},
                       {40,33, 0},{42,36, 0},{44,37, 0},{47,40, 0},{50,43, 0},
                       {52,44, 0},{55,47, 0},{57,48, 0},{59,51, 0},{63,54, 0},
                       {25,19,14},{27,20,15},{29,22,16},{32,24,18},{34,25,19},
                       {37,28,21},{40,30,22},{42,32,24},{44,33,25},{47,35,27},
                       {50,38,28},{52,40,30},{55,41,31},{57,43,33},{59,45,34},
                       {63,48,37}};

void init_graphics(){
  int i, j;
  char r,g,b;

  /* set 320x200x256 screen mode */
  asm{
    mov ax, 0013h
    int 10h
  }

  /* initialize palette */
  for(i=0; i<256; i++){
    r = colormap[i][0];
    g = colormap[i][1];
    b = colormap[i][2];
    asm{
      mov dh, r
      mov ch, g
      mov cl, b
      mov ax, 1010h
      mov bx, i
      int 10h
    }
  }
}

void plot_raster(unsigned char raster[160], int line){
  unsigned char x, color;
  unsigned int far *scr=(int far *)(0xa0000000L+(long)line*320L);
  static char screen[32000]; /* 200 x 160 */
  char *currline = screen+line*160;

  for (x=0; x<160; x++){
    color=raster[x];
    if(currline[x] != color){
      scr[x] = (color<<8)|color;
      currline[x] = color;
    }
  }
}

void reset_screen(){
  asm{
    mov ax, 0003h
    int 10h
  }
}
