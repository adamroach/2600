/* screen2.h

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

   Simple routines to manipulate a second (monochrome)
   moitor for debugging purposes.

*/

void setjump(char newjump);
void moveto2(char x, char y);
void plotchar2(char x, char y, char attr, char letter);
void clrscr2();
void scrollscr2(char lines);
int printf2(char *txt, ...);
