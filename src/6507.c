/* 6507.c

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

  This module provides the emulation for the mc6507 chip used by
  the Atari 2600s. The 6507 is the same as a 6502 with two
  exceptions: it has only 13 address lines (and can consequently
  access only 8k of memory) and no external interrupt lines are
  present.

  This emulation has been modified to accomodate the special chips
  accessed on the 2600.

*/

#include <stdio.h>
#include "6502.h"
#include "2600.h"
#include "riot.h"
#include "stella.h"

/* #undef DEBUG */

static unsigned char A;      /* Accumulator */
static unsigned char AH, AL; /* Accumulator nybbles for BCD calc */
static unsigned char X, Y;   /* Index Registers */
static unsigned int  PC;     /* Program Counter */
static unsigned char SP;     /* Stack Pointer */

static unsigned char bank = 0;   /* Current Bank */
static unsigned char bank_scheme = 1; /* 8k carts */

static FLAG          N;      /* negative flag */
static FLAG          V;      /* overflow flag */
static FLAG          B;      /* break flag */
static FLAG          D;      /* BCD flag */
static FLAG          I;      /* IRQ disable flag */
static FLAG          Z;      /* zero flag */
static FLAG          C;      /* carry flag */

#define printf2 fflush(stdout);printf

#define SETP(x) N=(x)&128;V=(x)&64;B=(x)&16;D=(x)&8;I=(x)&4;Z=(x)&2;C=(x)&1
#define P ((N?128:0)|(V?64:0)|(B?16:0)|(D?8:0)|(I?4:0)|(Z?2:0)|(C?1:0))
                             /* processor register macros */

#define SETP_NZ(x)   N=(x)&0x80;Z=!((x)&0xFF)

/* static unsigned char memory[0x2000]; */
/* static unsigned char memspace[0x4000]; */
static unsigned char *memspace;
static unsigned char *memory; /* = memspace; */

#define WRITE_CYCLES 3

#define PUSH(x) memory[(unsigned int)(SP--)|0x100]=(x);\
                if(!SP&0x80) bad_push(inst)
#define POP() (memory[(unsigned int)(++SP)|0x100]);\
                if(!SP&0x80) bad_pop(inst)
#define HI_BYTE(x) ((x)>>8)
#define LO_BYTE(x) ((x)&0xFF)

void die(){
  printf("Terminal error; exiting\n");
  reset_io();
  exit(1);
}

void init_6507(int addr, int brkflag){
#ifdef DEBUG
  printf2("Initializing 6507 chip\n");
#endif
  A=X=Y=0x00;
  SP=0xFF;
  /* Normal 65xx family entry point is at 0xE000. */
  PC=addr;
  /* PC = (memory[0x1FFA] | (memory[0x1FFB]<<8)); */
  PC = (memory[0x1FFC] | (memory[0x1FFD]<<8));
  if(brkflag) PC = (memory[0x1FFE] | (memory[0x1FFF]<<8));
  SETP(0);
}

int readrom(char *name, unsigned int location){
  FILE *romfile;
  unsigned int i = location;
  char flag;
  memory=memspace=(char *)malloc(0x4000);
  if(memory == NULL){
    reset_screen();
    printf("Malloc() failed\n");
    die();
  }
#ifdef DEBUG
  printf2("Memory allocated at %X\n",memory);
#endif
  memory[0x1ffe] = 0x00; /* setup break vector */
  memory[0x1fff] = 0x10;
  romfile = fopen(name,"rb");
  if(romfile == NULL){
    reset_screen();
    printf("No such file: %s\n",name);
    die();
  }
  while(!feof(romfile) && i <= 0x4000){
    memory[i++] = fgetc(romfile);
    if(!(i&0x0FFF)) i+=0x1000;
  }
  /* mirror 2k cartridges */

  flag = 1;
  for(i=0x1000; i<0x1800;i++){
    if (memory[i] != 0xFF) flag = 0;
  }
  if(flag){
    for(i=0x1000; i<0x1800; i++){
      memory[i] = memory[i+0x1800];
    }
  }

  return(1); /* ideally, will return 0 on failure. */
}


/* Memory map:
   0x0000 - 0x007F Stella Chip Registers (Video & Audio control) [& 0x7F]
   0x0080 - 0x00FF RIOT Chip Ram                                 [& 0x7F]
   0x0100 - 0x01FF Mirror of 0x0000 - 0x00FF
   0x0200 - 0x027F Stella Mirror ?
   0x0280 - 0x02FF RIOT Chip Registers (Input & timer control)   [& 0x7F]
   0x0300 - 0x03FF Mirror of 0x200-0x2FF
   0x0400 - 0x0FFF Stella Mirror ?
   0x1000 - 0x1FFF ROM Cartridge                                 [& 0xFFF]
*/


void disasm(struct table *inst){
  printf2("A:%02X X:%02X Y:%02X S:%02X   %s%s%s%s%s%s%s\t",A,X,Y,SP,
          N?"N":"-",V?"V":"-",B?"B":"-",D?"D":"-",I?"I":"-",
          Z?"Z":"-",C?"C":"-");
  if(inst->flags & REL){
      printf2("%04X  %02X %02X ..  \t%s ",PC,memory[PC], memory[PC+1],
                                                  inst->mnemonic);
      printf2("$%04X",PC+(char)memory[PC+1]+2);
  } else switch (inst->length){
    case 1:
      printf2("%04X  %02X .. ..  \t%s ",PC,memory[PC],inst->mnemonic);
    break;
    case 2:
      printf2("%04X  %02X %02X ..  \t%s ",PC,memory[PC], memory[PC+1],
                                                  inst->mnemonic);
      printf2(form[inst->mode],memory[PC+1]);
    break;
    case 3:
      printf2("%04X  %02X %02X %02X  \t%s ",PC,memory[PC], memory[PC+1],
                                       memory[PC+2],inst->mnemonic);
      printf2(form[inst->mode],memory[PC+2],memory[PC+1]);
    break;
    default:
      printf2("%04X  %02X %02X %02X  \t",PC,memory[PC], memory[PC+1],
                                      memory[PC+2]);
      printf2("Bad opcode; length = %d",inst->length);
  }
  printf2("\n");
}

void bad_push(struct table *inst){
  reset_screen();
  printf("Push to Stella memory\n\n");
  disasm(inst); 
  die();
}

void bad_pop(struct table *inst){
  reset_screen();
  printf("Pop from to Stella memory\n\n");
  disasm(inst);
  die();
}

int loop_6507(){
  unsigned char opcode;
  struct table *inst;
  unsigned char *arg;
  unsigned int temp;
  unsigned int mempos;
  unsigned char cycles, extra_cycles;

  fflush(stdout);

  while(1){
    extra_cycles = 0;
    PC &= 0x1FFF; /* Only 13 Address pins */
    opcode = memory[PC];
    inst = op_tabl+opcode;

    if(!inst->mode || inst->length < 1){
      reset_screen();
      printf("Bad opcode: 0x%02X at 0x%04X\n",opcode,PC);
      printf(" Mnemonic: %s\n Instr:    %d\n Mode:     %d\n"
             " Length:   %d\n Cycles:   %d\n Flags:    %d\n\n",
             inst->mnemonic, (int)inst->instruction,
             (int)inst->mode, (int)inst->length,
             (int)inst->cycles, (int)inst->flags);
      printf("Bank: %d\n\n",(int)bank);
      die();
    }

    switch(inst->mode){
      case ABS:
        mempos = ((memory[PC+2]<<8)|memory[PC+1]);
        mempos &= 0x1fff;
        arg = memory + mempos;
      break;

      case ACC:
        arg = &A;
        mempos = 0x1fff;
      break;

      case AX:
        mempos = (((memory[PC+2]<<8)|memory[PC+1])+X);
        mempos &= 0x1fff;
        arg = memory + mempos;
        /* Calculate extra cycles for page boundry crossing reads */
        if (((mempos & 0xff) < memory[PC+1]) && (inst->flags & READ))
          extra_cycles++;
      break;

      case AY:
        mempos = (((memory[PC+2]<<8)|memory[PC+1])+Y);
        mempos &= 0x1fff;
        arg = memory + mempos;
        /* Calculate extra cycles for page boundry crossing reads */
        if (((mempos & 0xff) < memory[PC+1]) && (inst->flags & READ))
          extra_cycles++;
      break;

      case IMM:
        mempos = (PC+1);
        mempos &= 0x1fff;
        arg = memory + mempos;
      break;

      case IMPL:
        arg = NULL;
        mempos = 0x1fff;
      break;

      case INDR:
        mempos = ((memory[PC+2]<<8)|memory[PC+1]);
        mempos &= 0x1fff;
        mempos = ((memory[mempos+1]<<8)|memory[mempos]);
        mempos &= 0x1fff;
        arg = memory + mempos;
      break;

      case IX: /* (zp,X) */
        mempos = (memory[(memory[PC+1]+X)&0xff] |
              (memory[(memory[PC+1]+X+1)&0xff]<<8));
        mempos &= 0x1fff;
        arg = memory + mempos;
      break;

      case IY: /* (zp),Y */
        mempos = ((memory[(memory[PC+1])&0xff] |
                     (memory[(memory[PC+1]+1)&0xff]<<8)));
        temp = mempos; mempos += Y;
        /* Calculate extra cycles for page boundary crossing reads */
        if (((mempos & 0xff) < (temp & 0xff)) && (inst->flags & READ))
          extra_cycles++;
        mempos &= 0x1fff;
        arg = memory + mempos;
      break;

      case ZABS:
        mempos = (memory[PC+1]);
        arg = memory + mempos;
      break;

      case ZAX:
        mempos = ((memory[PC+1]+X)&0xff);
        arg = memory + mempos;
      break;

      case ZAY:
        mempos = ((memory[PC+1]+Y)&0xff);
        arg = memory + mempos;
      break;
    }

    /* Mirror RAM & Stella */
    /* if (mempos >= 0x0100 && mempos <= 0x01FF){ */
    if ((mempos & 0x0100) && !(mempos & 0xFE00)){
      mempos &= 0x00FF;
      arg = memory + mempos;
    }

    /* Mirror RIOT: 380-3ff maps to 280-2ff */
    /* if (mempos >= 0x0380 && mempos <= 0x03FF){ */
    if ((mempos & 0x0380) && !(mempos & 0xFC00)){
      mempos &= 0x02FF;
      arg = memory + mempos;
    }


  /*************************************************************************/

  #ifdef DEBUG
    /* disasm(inst);    */
  #endif

    /* We're counting in stella cycles, since they are the finest
       granularity we'll need. This keeps the riot and stella chips
       in closer sync. */

    cycles = (inst->cycles+extra_cycles)*3;
    stella_cycle(cycles-WRITE_CYCLES);
    riot_cycle(cycles-WRITE_CYCLES);
    extra_cycles = 0;

    if(inst->flags & READ){ /* Check for STELLA or RIOT read accesses */
      if((mempos & 0x0200) && (!(mempos & 0xfc00))){ /* RIOT Access */
        (*arg) = riot_read(mempos & 0x3f);
      } else if((mempos < 0x80 || mempos > 0xFF)
               && (mempos < 0x1000)){ /* Stella Access */
        (*arg) = stella_read(mempos & 0x0f);
/*        printf("0x%x = 0x%x\n",mempos,*arg); */
      }
    }

  /*************************************************************************/

    switch(inst->instruction){

      case ADC:/* NZCV */
        if(D){ /* Binary Coded Decimal calculation */
          AL = (A & 0x0F) + ((*arg) & 0x0F) + (C?1:0);
          if(AL > 9) AL += 6;                 /* Fix lower nybble */
          AH = (A >> 4) + ((*arg) >> 4) + ((AL & 0xF0)?1:0);
          Z = !((A + (*arg) + (C?1:0))&0xFF); /* set Z flag */
          N = (AH & 0x08);                    /* set N flag */
          V = (N && !(A & 0x80));             /* set V flag */
          if(AH > 9) AH += 6;                 /* Fix upper nybble */
          C = (AH & 0xF0);                    /* Set C flag */
          A = ((AH << 4) | (AL & 0x0F));
        } else { /* binary calculation */
          temp = (unsigned int)A + (unsigned int)(*arg) + (C?1:0);
          V = ((temp & 0x80) && !(A & 0x80)); /* result is neg, A is not */
          A = temp & 0xFF;
          C = (temp & 0xFF00) >> 8;
          SETP_NZ(A);
        }
      break;

      case AND: /* NZ */
        A &= (*arg);
        SETP_NZ(A);
      break;

      case ASL: /* NZC */
        C = ((*arg) & 0x80);
        (*arg) <<= 1;
        SETP_NZ(*arg);
      break;

      case BCC:
        if(!C){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BCS:
        if(C){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BEQ:
        if(Z){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BIT: /* NZV -- special case */
         Z= ~((*arg)&A); N=((*arg)&128); V=((*arg)&64);
      break;

      case BMI:
        if(N){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BNE:
        if(!Z){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BPL:
        if(!N){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BRK: /* B */
        PC += 1;
        PUSH(HI_BYTE(PC));
        PUSH(LO_BYTE(PC));
        PUSH(P);
        B = 1;
        PC = (memory[0x1FFE] | (memory[0x1FFF]<<8)) - 1;
        /* the above line would be FFFE/FFFF for the 6502 */
      break;

      case BVC:
        if(!V){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case BVS:
        if(V){
          temp = PC;
          PC += (char)memory[PC+1];
          extra_cycles++;
          if((temp & 0xff00) != (PC & 0xff00)) extra_cycles++;
        }
      break;

      case CLC: /* C */
        C = 0;
      break;

      case CLD: /* D */
        D = 0;
      break;

      case CLI: /* I */
        I = 0;
      break;

      case CLV: /* V */
        V = 0;
      break;

      case CMP: /* NZC */
        C = (A >= (*arg));
        temp = (int)A - (*arg);
        SETP_NZ(temp);
      break;

      case CPX: /* NZC */
        C = (X >= (*arg));
        temp = (int)X - (*arg);
        SETP_NZ(temp);
      break;

      case CPY: /* NZC */
        C = (Y >= (*arg));
        temp = (int)Y - (*arg);
        SETP_NZ(temp);
      break;

      case DEC: /* NZ */
        (*arg)--;
        SETP_NZ(*arg);
      break;

      case DEX: /* NZ */
        X--;
        SETP_NZ(X);
      break;

      case DEY: /* NZ */
        Y--;
        SETP_NZ(Y);
      break;

      case EOR: /* NZ */
        A ^= (*arg);
        SETP_NZ(A);
      break;

      case INC: /* NZ */
        (*arg)++;
        SETP_NZ(*arg);
      break;

      case INX: /* NZ */
        X++;
        SETP_NZ(X);
      break;

      case INY: /* NZ */
        Y++;
        SETP_NZ(Y);
      break;

      case JSR:
        temp = PC + 2; /* instruction is 3 bytes long, but we push (ret-1) */
        PUSH(HI_BYTE(temp));
        PUSH(LO_BYTE(temp));

        /* Flow through to JMP for actual jump */

      case JMP:
        PC = mempos - inst->length;
      break;

      case LDA: /* NZ */
        A = (*arg);
        SETP_NZ(A);
      break;

      case LDX: /* NZ */
        X = (*arg);
        SETP_NZ(X);
      break;

      case LDY: /* NZ */
        Y = (*arg);
        SETP_NZ(Y);
      break;

      case LSR: /* NZC */
        C = ((*arg) & 0x01);
        (*arg) >>= 1;
        SETP_NZ(*arg);
      break;

      case NOP:
      break;

      case ORA: /* NZ */
        A |= (*arg);
        SETP_NZ(A);
      break;

      case PHA:
        if(!(SP & 0x80)){ /* Stella Write  -- TIMING MAY BE WRONG */
          stella_write(SP & 0x3f, A);
          SP--;
        } else PUSH(A);
      break;

      case PHP:
        if(!(SP & 0x80)){ /* Stella Write -- TIMING MAY BE WRONG */
          stella_write(SP & 0x3f, P);
          SP--;
        } else PUSH(P);
      break;

      case PLA: /* NZ */
         A = POP();
        SETP_NZ(A);
      break;

      case PLP: /* NZCIDV */
        /* Be careful here; we can't include POP() in SETP(), since
           SETP() is a macro -- POP() would be evaluated several times. */
        temp = POP(); SETP(temp);
      break;

      case ROL: /* NZC */
        C=C?1:0;
        temp = ((*arg)&0x80);
        (*arg) <<= 1;
        (*arg) |= C;
        C = temp;
        SETP_NZ(*arg);
      break;

      case ROR: /* NZC */
        C=C?128:0;
        temp = ((*arg)&0x01);
        (*arg) >>= 1;
        (*arg) |= C;
        C = temp;
        SETP_NZ(*arg);
      break;

      case RTI: /* NZCIDV */
        /* Be careful here; we can't include POP() in SETP(), since
           SETP() is a macro -- POP() would be evaluated several times. */

        temp = POP(); SETP(temp);

      /* Fall through to RTS for actual return */

      case RTS:
        PC = POP();
        temp = POP();
        PC |= temp << 8;
        if(inst->instruction == RTI){PC -= 1;}
      break;

      case SBC: /* NZCV */
        if(D){ /* Binary Coded Decimal calculation */
          AL = (A & 0x0F) - ((*arg) & 0x0F) - (C?0:1);
          if (AL & 0x10) AL -= 6;             /* Fix lower nybble */
          AH = (A >> 4) - ((*arg) >> 4) - ((AL & 0x10)?1:0);
          if (AH & 0x10) AH -= 6;             /* Fix upper nybble */
          /* set flags just like non-BCD calculation */
          temp = A - (*arg) - (C?1:0);
          V = (!(temp & 0x80) & (A & 0x80));
          C = !((temp & 0xFF00) >> 8);
          SETP_NZ(temp);
          A = ((AH << 4) | (AL & 0x0F));
        } else { /* Binary calculation */
          temp = (unsigned int)A - (unsigned int)(*arg) - (C?0:1);
          V = (!(temp & 0x80) && (A & 0x80)); /* result is pos, A is not */
          A = temp & 0xFF;
          C = !((temp & 0xFF00) >> 8);
          SETP_NZ(A);
        }
      break;

      case SEC: /* C */
        C = 1;
      break;

      case SED: /* D */
        D = 1;
      break;

      case SEI: /* I */
        I = 1;
      break;

      case STA:
        (*arg) = A;
      break;

      case STX:
        (*arg) = X;
      break;

      case STY:
        (*arg) = Y;
      break;

      case TAX: /* NZ */
        X = A;
        SETP_NZ(X);
      break;

      case TAY: /* NZ */
        Y = A;
        SETP_NZ(Y);
      break;

      case TSX: /* NZ */
        X = SP;
        SETP_NZ(X);
      break;

      case TXA: /* NZ */
        A = X;
        SETP_NZ(A);
      break;

      case TXS:
        SP = X;
      break;

      case TYA: /* NZ */
        A = Y;
        SETP_NZ(A);
      break;

    }

     if(inst->flags & WRITE){ /* Check for STELLA or RIOT write accesses */
      if((mempos & 0x0200) && (!(mempos & 0xfc00))){ /* RIOT Access */
        riot_write(mempos & 0x3f, (*arg));
      }
      else if(mempos < 0x80 || mempos > 0xFF){ /* Stella Access */
        stella_write(mempos & 0x3f, (*arg));
      }
      if(mempos & 0xF000){
        switch (bank_scheme){
          case 1:
            switch(mempos & 0x1FFF){
              case 0x1FF8: bank = 0; break;
              case 0x1FF9: bank = 1; break;
              default:
                reset_screen();
                printf("Attempt to modify ROM (0x%04X).\n", mempos);
                disasm(inst);
                die();
            }
            memory = memspace + (0x2000 * bank);
            break;
          case 0:
          default:
            reset_screen();
            printf("Attempt to modify ROM (0x%04X).\n", mempos);
            disasm(inst);
            die();
        }
      }
    }

    stella_cycle(WRITE_CYCLES+extra_cycles*3);
    riot_cycle(WRITE_CYCLES+extra_cycles*3);

    PC += inst->length;

  }
}
