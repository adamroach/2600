/* dasm.c

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

  Quick, hacked together disassembler.

*/

#include <stdio.h>
#include <stdlib.h>
#include "6502.h"

extern int getopt(int,char **,char *);

int Start = 0x1000;
int Size = 0; /* default to whole cart */
int End = 0;
char rom_file[20];
unsigned char memory[1024*16 + 0x1000]; 
/* 16k is the largest cart we'll handle */

void showusage(char *name){
  printf("Usage: %s [-b begin] [-s size | -e end] romfile\n", name);
  exit(1);
}

void getswitches(int argc, char **argv){
  int c;
  extern char *optarg;
  extern int optind;
 
  while ((c = getopt(argc, argv, "b:s:e:")) != -1){
    switch(c){
      case 'b':
        sscanf(optarg,"%X",&Start);
        break;
      case 's':
        if (End) showusage(argv[0]);
        sscanf(optarg,"%X",&Size);
        break;
      case 'e':
        if (Size) showusage(argv[0]);
        sscanf(optarg,"%X",&End);
        break;
      case '?':
      default:
        showusage(argv[0]);
      }
    }
  if((argc - optind) != 1){
    showusage(argv[0]);
  } else {
    strcpy(rom_file,argv[optind]);
  }
}

int readrom(char *name, unsigned int location){
  FILE *romfile;
  unsigned int i = location;
  romfile = fopen(name,"rb");
  if(romfile == NULL){
    printf("No such file: %s\n",name);
    return(-1);
  }
  while(!feof(romfile) && i <= 0x4000){
    memory[i++] = fgetc(romfile);
  }
  fclose(romfile);
  return(i-location);
}

void disasm(struct table *inst, int PC){
  if(inst->flags & REL){
      printf("%04X  %02X %02X ..  \t%s ",PC,memory[PC], memory[PC+1],
                                                  inst->mnemonic);
      printf("$%04X",PC+(char)memory[PC+1]+2);
  } else switch (inst->length) {
    case 1:
      printf("%04X  %02X .. ..  \t%s ",PC,memory[PC],inst->mnemonic);
    break;
    case 2:
      printf("%04X  %02X %02X ..  \t%s ",PC,memory[PC], memory[PC+1],
                                                  inst->mnemonic);
      printf(form[inst->mode],memory[PC+1]);
    break;
    case 3:
      printf("%04X  %02X %02X %02X  \t%s ",PC,memory[PC], memory[PC+1],
                                       memory[PC+2],inst->mnemonic);
      printf(form[inst->mode],memory[PC+2],memory[PC+1]);
    break;
    default:
      printf("%04X  %02X .. ..  \t",PC,memory[PC]);
      printf("---");
  }
  printf("\n");
}

void dasm(int start, int size){
  struct table *inst;
  int end = start+size;
  int curr = start;
  while(curr < end){
    inst = op_tabl + memory[curr];
    disasm(inst, curr);
    if (inst -> length == 0){
      curr ++;
    } else {
      curr += inst -> length;
    }
  }
}

main(int argc, char **argv){
  int romsize;
  getswitches(argc, argv);
  romsize = readrom(rom_file,0x1000);
  if (romsize == -1) exit(1);
  if (!Size && !End) Size = romsize;
  if (End) Size = End - Start + 1;
  dasm(Start, Size);
}
