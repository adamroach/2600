/*
  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms
*/

#include <stdarg.h>

char curx, cury;
char height = 25;
char width = 80;
char jump = 1;

void moveto2(char x, char y){
  curx = x; cury = y;
}

void setjump(char newjump){
  jump = newjump;
}

void plotchar2(char x, char y, char attr, char letter){
  unsigned char far *rgen = (char far *)(0xB0000000L+y*160+x*2);
	*rgen=letter; *(rgen+1) = attr;
}

void clrscr2(){
  int x, y;
  for(x=0;x<width;x++)
    for(y=0;y<height;y++)
      plotchar2(x,y,16,' ');
  moveto2(0,0);
}

void scrollscr2(char lines){
  unsigned char far *screen = (char far *)(0xB0000000L);
  int i;
  for (i=0;i<(width*(height-lines))*2; i++){
    screen[i]=screen[i+width*2*lines];
  }
  for(;i<width*height*2;i+=2) screen[i]=' ';
}

int printf2(char *txt, ...){
  int ret, i;
  int textattr = 15;
  char buf[256];
  va_list prms;
  va_start(prms,txt);
  ret=vsprintf(buf,txt,prms);

  for(i=0;buf[i];i++){
    switch(buf[i]){
      case 9:  /* Handle tabs */
          curx = ((curx+8)>>3)<<3;
        break;
      case 10: /* Handle carriage returns */
        curx = 0;
        if(++cury >= height){
          scrollscr2(jump);
          cury-=jump;
        }
        break;
      default:
        plotchar2(curx++, cury, textattr, buf[i]);
        if(curx >= width){
          curx = 0;
          if(++cury >= height){
            scrollscr2(jump);
            cury-=jump;
          }
        }
        break;
    } /* end of switch */
  }
  return(ret);
}
