/* 2600.c

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "2600.h"
#include "stella.h"
#include "riot.h"
#include "io.h"

#define printf2 printf
#define clrscr2() printf("");
#define setjump(x) printf("");

extern int getopt(int,char **,char *);

char rom_file[20];
unsigned int start_addr = 0x1000;
unsigned char brkflag = 0;

void showusage(char *name){
  printf("Usage: %s [-a <address>] [-b] romfile\n", name);
  printf("  -a <address> Begin execution at <address> (in hex)\n");
  printf("  -b           Begin execution at break vector\n");
  printf("  -f <rate>    Set frame skip rate\n");
  exit(1);
}

void getswitches(int argc, char **argv){
  int c;
  extern char *optarg;
  extern int optind;

  while ((c = getopt(argc, argv, "a:bf:")) != -1){
    switch(c){
      case 'a':
        printf("Starting at $%X\n",start_addr); fflush(stdout);
        printf("Wait... you asked for %s\n",optarg); fflush(stdout);
        sscanf(optarg,"%X",&start_addr);
        printf("Starting at $%X\n",start_addr); fflush(stdout);
        break;
      case 'b':
        brkflag = 1;
        break;
      case 'f':
        framerate = atoi(optarg);
        break;
      case '?':
        showusage(argv[0]);
    }
  }
  if((argc - optind) != 1){
    showusage(argv[0]);
  } else {
    strcpy(rom_file,argv[optind]);
  }
}

void main(int argc, char **argv){
  getswitches(argc, argv);
#ifdef DEBUG
  clrscr2();
  setjump(12);
  printf2("Reading rom image...\n");
#endif
  readrom(rom_file,0x1000);
#ifdef DEBUG
  printf2("Initializing chips...\n");
#endif
  init_6507(start_addr,brkflag);
  init_io();
  init_stella();
  init_riot();
#ifdef DEBUG
  printf2("Entering executive loop...\n");
  fflush(stdout);
#endif
  loop_6507();
  reset_screen();
}
