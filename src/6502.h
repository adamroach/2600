/* 6502.h

  Copyright 1995, 2023 by Adam Roach
  See LICENSE file for licensing terms

  This file contains timing and length information for each opcode used
  by the 6502 chip. It is included into the 6502.c module.

*/


/* Opcodes */

#define ADC_ABS    0x6D
#define ADC_AX     0x7D
#define ADC_AY     0x79
#define ADC_IMM    0x69
#define ADC_IX     0x61
#define ADC_IY     0x71
#define ADC_ZABS   0x65
#define ADC_ZAX    0x75
#define AND_ABS    0x2D
#define AND_AX     0x3D
#define AND_AY     0x39
#define AND_IMM    0x29
#define AND_IX     0x21
#define AND_IY     0x31
#define AND_ZABS   0x25
#define AND_ZAX    0x35
#define ASL_ABS    0x0E
#define ASL_ACC    0x0A
#define ASL_AX     0x1E
#define ASL_ZABS   0x06
#define ASL_ZAX    0x16
#define BCC_ABS    0x90
#define BCS_ABS    0xB0
#define BEQ_ABS    0xF0
#define BIT_ABS    0x2C
#define BIT_ZABS   0x24
#define BMI_ABS    0x30
#define BNE_ABS    0xD0
#define BPL_ABS    0x10
#define BRK_IMPL   0x00
#define BVC_ABS    0x50
#define BVS_ABS    0x70
#define CLC_IMPL   0x18
#define CLD_IMPL   0xD8
#define CLI_IMPL   0x58
#define CLV_IMPL   0xB8
#define CMP_ABS    0xCD
#define CMP_AX     0xDD
#define CMP_AY     0xD9
#define CMP_IMM    0xC9
#define CMP_IX     0xC1
#define CMP_IY     0xD1
#define CMP_ZABS   0xC5
#define CMP_ZAX    0xD5
#define CPX_ABS    0xEC
#define CPX_IMM    0xE0
#define CPX_ZABS   0xE4
#define CPY_ABS    0xCC
#define CPY_IMM    0xC0
#define CPY_ZABS   0xC4
#define DEC_ABS    0xCE
#define DEC_AX     0xDE
#define DEC_ZABS   0xC6
#define DEC_ZAX    0xD6
#define DEX_IMPL   0xCA
#define DEY_IMPL   0x88
#define EOR_ABS    0x4D
#define EOR_AX     0x5D
#define EOR_AY     0x59
#define EOR_IMM    0x49
#define EOR_IX     0x41
#define EOR_IY     0x51
#define EOR_ZABS   0x45
#define EOR_ZAX    0x55
#define INC_ABS    0xEE
#define INC_AX     0xFE
#define INC_ZABS   0xE6
#define INC_ZAX    0xF6
#define INX_IMPL   0xE8
#define INY_IMPL   0xC8
#define JMP_ABS    0x4C
#define JMP_INDR   0x6C
#define JSR_ABS    0x20
#define LDA_ABS    0xAD
#define LDA_AX     0xBD
#define LDA_AY     0xB9
#define LDA_IMM    0xA9
#define LDA_IX     0xA1
#define LDA_IY     0xB1
#define LDA_ZABS   0xA5
#define LDA_ZAX    0xB5
#define LDX_ABS    0xAE
#define LDX_AY     0xBE
#define LDX_IMM    0xA2
#define LDX_ZABS   0xA6
#define LDX_ZAY    0xB6
#define LDY_ABS    0xAC
#define LDY_AX     0xBC
#define LDY_IMM    0xA0
#define LDY_ZABS   0xA4
#define LDY_ZAX    0xB4
#define LSR_ABS    0x4E
#define LSR_ACC    0x4A
#define LSR_AX     0x5E
#define LSR_ZABS   0x46
#define LSR_ZAX    0x56
#define NOP_IMPL   0xEA
#define ORA_ABS    0x0D
#define ORA_AX     0x1D
#define ORA_AY     0x19
#define ORA_IMM    0x09
#define ORA_IX     0x01
#define ORA_IY     0x11
#define ORA_ZABS   0x05
#define ORA_ZAX    0x15
#define PHA_IMPL   0x48
#define PHP_IMPL   0x08
#define PLA_IMPL   0x68
#define PLP_IMPL   0x28
#define ROL_ABS    0x2E
#define ROL_ACC    0x2A
#define ROL_AX     0x3E
#define ROL_ZABS   0x26
#define ROL_ZAX    0x36
#define ROR_ABS    0x6E
#define ROR_ACC    0x6A
#define ROR_AX     0x7E
#define ROR_ZABS   0x66
#define ROR_ZAX    0x76
#define RTI_IMPL   0x40
#define RTS_IMPL   0x60
#define SBC_ABS    0xED
#define SBC_AX     0xFD
#define SBC_AY     0xF9
#define SBC_IMM    0xE9
#define SBC_IX     0xE1
#define SBC_IY     0xF1
#define SBC_ZABS   0xE5
#define SBC_ZAX    0xF5
#define SEC_IMPL   0x38
#define SED_IMPL   0xF8
#define SEI_IMPL   0x78
#define STA_ABS    0x8D
#define STA_AX     0x9D
#define STA_AY     0x99
#define STA_IX     0x81
#define STA_IY     0x91
#define STA_ZABS   0x85
#define STA_ZAX    0x95
#define STX_ABS    0x8E
#define STX_ZABS   0x86
#define STX_ZAY    0x96
#define STY_ABS    0x8C
#define STY_ZAX    0x94
#define STY_ZABS   0x84
#define TAX_IMPL   0xAA
#define TAY_IMPL   0xA8
#define TSX_IMPL   0xBA
#define TXA_IMPL   0x8A
#define TXS_IMPL   0x9A
#define TYA_IMPL   0x98

/* Mnemonics */

#define ADC       1
#define AND       2
#define ASL       3
#define BCC       4
#define BCS       5
#define BEQ       6
#define BIT       7
#define BMI       8
#define BNE       9
#define BPL       10
#define BRK       11
#define BVC       12
#define BVS       13
#define CLC       14
#define CLD       15
#define CLI       16
#define CLV       17
#define CMP       18
#define CPX       19
#define CPY       20
#define DEC       21
#define DEX       22
#define DEY       23
#define EOR       24
#define INC       25
#define INX       26
#define INY       27
#define JMP       28
#define JSR       29
#define LDA       30
#define LDX       31
#define LDY       32
#define LSR       33
#define NOP       34
#define ORA       35
#define PHA       36
#define PHP       37
#define PLA       38
#define PLP       39
#define ROL       40
#define ROR       41
#define RTI       42
#define RTS       43
#define SBC       44
#define SEC       45
#define SED       46
#define SEI       47
#define STA       48
#define STX       49
#define STY       50
#define TAX       51
#define TAY       52
#define TSX       53
#define TXA       54
#define TXS       55
#define TYA       56

/* Memory access modes */

#define ABS       1     /* Absolute */
#define ACC       2     /* Accumulator */
#define AX        3     /* Absolute, X indexed */
#define AY        4     /* Absolute, Y indexed */
#define IMM       5     /* Immediate */
#define IMPL      6     /* Implied */
#define INDR      7     /* Absolute Indirect */
#define IX        8     /* Zero Page X indexed Indirect */
#define IY        9     /* Zero Page Indirect, Y indexed */
#define ZABS      10    /* Zero Page Absolute */
#define ZAX       11    /* Zero Page Absolute, X indexed */
#define ZAY       12    /* Zero Page Absolute, Y indexed */

char *form[] ={ "",
                "$%02X%02X",      /* ABS */
                "",               /* ACC */
                "$%02X%02X,X",    /* AX */
                "$%02X%02X,Y",    /* AY */
                "#$%02X",         /* IMM */
                "",               /* IMPL */
                "($%02X%02X)",    /* INDR */
                "($%02X),Y",       /* IX */
                "($%02X,X)",       /* IY */
                "$%02X",           /* ZABS */
                "$%02X,X",         /* ZAX */
                "$%02X,Y" };       /* ZAY */

/* Flags */

#define READ    1
#define WRITE   2
#define REL     128

typedef unsigned char FLAG;

struct table{
  char* mnemonic;
  unsigned char  instruction;
  unsigned char  mode;
  unsigned char  length;
  unsigned char  cycles;
  unsigned char  flags; /* bit 0 = read; bit 1 = write; bit 7 = relative */
};

struct table op_tabl[] = {{ "BRK", BRK, IMPL, 1, 7, 0 },       /* 0x00 */
                          { "ORA", ORA, IX, 2, 6, 1 },         /* 0x01 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x02 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x03 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x04 */
                          { "ORA", ORA, ZABS, 2, 3, 1 },       /* 0x05 */
                          { "ASL", ASL, ZABS, 2, 5, 3 },       /* 0x06 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x07 */
                          { "PHP", PHP, IMPL, 1, 3, 0 },       /* 0x08 */
                          { "ORA", ORA, IMM, 2, 2, 0 },        /* 0x09 */
                          { "ASL", ASL, ACC, 1, 2, 0 },        /* 0x0A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x0B */
                          { "", 0, 0, 0, 0, 0 },               /* 0x0C */
                          { "ORA", ORA, ABS, 3, 4, 1 },        /* 0x0D */
                          { "ASL", ASL, ABS, 3, 6, 3 },        /* 0x0E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x0F */
                          { "BPL", BPL, ABS, 2, 2, REL },      /* 0x10 */
                          { "ORA", ORA, IY, 2, 5, 1 },         /* 0x11 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x12 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x13 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x14 */
                          { "ORA", ORA, ZAX, 2, 4, 1 },        /* 0x15 */
                          { "ASL", ASL, ZAX, 2, 6, 3 },        /* 0x16 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x17 */
                          { "CLC", CLC, IMPL, 1, 2, 0 },       /* 0x18 */
                          { "ORA", ORA, AY, 3, 4, 1 },         /* 0x19 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x1A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x1B */
                          { "", 0, 0, 0, 0, 0 },               /* 0x1C */
                          { "ORA", ORA, AX, 3, 4, 1 },         /* 0x1D */
                          { "ASL", ASL, AX, 3, 7, 1 },         /* 0x1E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x1F */
                          { "JSR", JSR, ABS, 3, 6, 0 },        /* 0x20 */
                          { "AND", AND, IX, 2, 6, 1 },         /* 0x21 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x22 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x23 */
                          { "BIT", BIT, ZABS, 2, 3, 1 },       /* 0x24 */
                          { "AND", AND, ZABS, 2, 3, 1 },       /* 0x25 */
                          { "ROL", ROL, ZABS, 2, 5, 3 },       /* 0x26 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x27 */
                          { "PLP", PLP, IMPL, 1, 4, 0 },       /* 0x28 */
                          { "AND", AND, IMM, 2, 2, 0 },        /* 0x29 */
                          { "ROL", ROL, ACC, 1, 2, 0 },        /* 0x2A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x2B */
                          { "BIT", BIT, ABS, 3, 4, 1 },        /* 0x2C */
                          { "AND", AND, ABS, 3, 4, 1 },        /* 0x2D */
                          { "ROL", ROL, ABS, 3, 6, 3 },        /* 0x2E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x2F */
                          { "BMI", BMI, ABS, 2, 2, REL },      /* 0x30 */
                          { "AND", AND, IY, 2, 5, 1 },         /* 0x31 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x32 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x33 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x34 */
                          { "AND", AND, ZAX, 2, 4, 1 },        /* 0x35 */
                          { "ROL", ROL, ZAX, 2, 6, 3 },        /* 0x36 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x37 */
                          { "SEC", SEC, IMPL, 1, 2, 0 },       /* 0x38 */
                          { "AND", AND, AY, 3, 4, 1 },         /* 0x39 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x3A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x3B */
                          { "", 0, 0, 0, 0, 0 },               /* 0x3C */
                          { "AND", AND, AX, 3, 4, 1 },         /* 0x3D */
                          { "ROL", ROL, AX, 3, 7, 3 },         /* 0x3E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x3F */
                          { "RTI", RTI, IMPL, 1, 6, 0 },       /* 0x40 */
                          { "EOR", EOR, IX, 2, 6, 1 },         /* 0x41 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x42 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x43 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x44 */
                          { "EOR", EOR, ZABS, 2, 3, 1 },       /* 0x45 */
                          { "LSR", LSR, ZABS, 2, 5, 3 },       /* 0x46 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x47 */
                          { "PHA", PHA, IMPL, 1, 3, 0 },       /* 0x48 */
                          { "EOR", EOR, IMM, 2, 2, 0 },        /* 0x49 */
                          { "LSR", LSR, ACC, 1, 2, 0 },        /* 0x4A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x4B */
                          { "JMP", JMP, ABS, 3, 3, 0 },        /* 0x4C */
                          { "EOR", EOR, ABS, 3, 4, 1 },        /* 0x4D */
                          { "LSR", LSR, ABS, 3, 6, 3 },        /* 0x4E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x4F */
                          { "BVC", BVC, ABS, 2, 2, REL },      /* 0x50 */
                          { "EOR", EOR, IY, 2, 5, 1 },         /* 0x51 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x52 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x53 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x54 */
                          { "EOR", EOR, ZAX, 2, 4, 1 },        /* 0x55 */
                          { "LSR", LSR, ZAX, 2, 6, 3 },        /* 0x56 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x57 */
                          { "CLI", CLI, IMPL, 1, 2, 0 },       /* 0x58 */
                          { "EOR", EOR, AY, 3, 4, 1 },         /* 0x59 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x5A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x5B */
                          { "", 0, 0, 0, 0, 0 },               /* 0x5C */
                          { "EOR", EOR, AX, 3, 4, 1 },         /* 0x5D */
                          { "LSR", LSR, AX, 3, 7, 3 },         /* 0x5E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x5F */
                          { "RTS", RTS, IMPL, 1, 6, 0 },       /* 0x60 */
                          { "ADC", ADC, IX, 2, 6, 1 },         /* 0x61 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x62 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x63 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x64 */
                          { "ADC", ADC, ZABS, 2, 3, 1 },       /* 0x65 */
                          { "ROR", ROR, ZABS, 2, 5, 3 },       /* 0x66 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x67 */
                          { "PLA", PLA, IMPL, 1, 4, 0 },       /* 0x68 */
                          { "ADC", ADC, IMM, 2, 2, 0 },        /* 0x69 */
                          { "ROR", ROR, ACC, 1, 2, 0 },        /* 0x6A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x6B */
                          { "JMP", JMP, INDR, 3, 5, 0 },       /* 0x6C */
                          { "ADC", ADC, ABS, 3, 4, 1 },        /* 0x6D */
                          { "ROR", ROR, ABS, 3, 6, 3 },        /* 0x6E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x6F */
                          { "BVS", BVS, ABS, 2, 2, REL },      /* 0x70 */
                          { "ADC", ADC, IY, 2, 5, 1 },         /* 0x71 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x72 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x73 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x74 */
                          { "ADC", ADC, ZAX, 2, 4, 1 },        /* 0x75 */
                          { "ROR", ROR, ZAX, 2, 6, 3 },        /* 0x76 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x77 */
                          { "SEI", SEI, IMPL, 1, 2, 0 },       /* 0x78 */
                          { "ADC", ADC, AY, 3, 4, 1 },         /* 0x79 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x7A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x7B */
                          { "", 0, 0, 0, 0, 0 },               /* 0x7C */
                          { "ADC", ADC, AX, 3, 4, 1 },         /* 0x7D */
                          { "ROR", ROR, AX, 3, 7, 3 },         /* 0x7E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x7F */
                          { "", 0, 0, 0, 0, 0 },               /* 0x80 */
                          { "STA", STA, IX, 2, 6, 2 },         /* 0x81 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x82 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x83 */
                          { "STY", STY, ZABS, 2, 3, 2 },       /* 0x84 */
                          { "STA", STA, ZABS, 2, 3, 2 },       /* 0x85 */
                          { "STX", STX, ZABS, 2, 3, 2 },       /* 0x86 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x87 */
                          { "DEY", DEY, IMPL, 1, 2, 0 },       /* 0x88 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x89 */
                          { "TXA", TXA, IMPL, 1, 2, 0 },       /* 0x8A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x8B */
                          { "STY", STY, ABS, 3, 4, 2 },        /* 0x8C */
                          { "STA", STA, ABS, 3, 4, 2 },        /* 0x8D */
                          { "STX", STX, ABS, 3, 4, 2 },        /* 0x8E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x8F */
                          { "BCC", BCC, ABS, 2, 2, REL },      /* 0x90 */
                          { "STA", STA, IY, 2, 6, 2 },         /* 0x91 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x92 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x93 */
                          { "STY", STY, ZAX, 2, 5, 2 },        /* 0x94 */
                          { "STA", STA, ZAX, 2, 4, 2 },        /* 0x95 */
                          { "STX", STX, ZAY, 2, 4, 2 },        /* 0x96 */
                          { "", 0, 0, 0, 0, 0 },               /* 0x97 */
                          { "TYA", TYA, IMPL, 1, 2, 0 },       /* 0x98 */
                          { "STA", STA, AY, 3, 5, 2 },         /* 0x99 */
                          { "TXS", TXS, IMPL, 1, 2, 0 },       /* 0x9A */
                          { "", 0, 0, 0, 0, 0 },               /* 0x9B */
                          { "", 0, 0, 0, 0, 0 },               /* 0x9C */
                          { "STA", STA, AX, 3, 5, 2 },         /* 0x9D */
                          { "", 0, 0, 0, 0, 0 },               /* 0x9E */
                          { "", 0, 0, 0, 0, 0 },               /* 0x9F */
                          { "LDY", LDY, IMM, 2, 2, 1 },        /* 0xA0 */
                          { "LDA", LDA, IX, 2, 6, 1 },         /* 0xA1 */
                          { "LDX", LDX, IMM, 2, 2, 1 },        /* 0xA2 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xA3 */
                          { "LDY", LDY, ZABS, 2, 3, 1 },       /* 0xA4 */
                          { "LDA", LDA, ZABS, 2, 3, 1 },       /* 0xA5 */
                          { "LDX", LDX, ZABS, 2, 3, 1 },       /* 0xA6 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xA7 */
                          { "TAY", TAY, IMPL, 1, 2, 0 },       /* 0xA8 */
                          { "LDA", LDA, IMM, 2, 2, 1 },        /* 0xA9 */
                          { "TAX", TAX, IMPL, 1, 2, 0 },       /* 0xAA */
                          { "", 0, 0, 0, 0, 0 },               /* 0xAB */
                          { "LDY", LDY, ABS, 3, 4, 1 },        /* 0xAC */
                          { "LDA", LDA, ABS, 3, 4, 1 },        /* 0xAD */
                          { "LDX", LDX, ABS, 3, 4, 1 },        /* 0xAE */
                          { "", 0, 0, 0, 0, 0 },               /* 0xAF */
                          { "BCS", BCS, ABS, 2, 2, REL },      /* 0xB0 */
                          { "LDA", LDA, IY, 2, 5, 1 },         /* 0xB1 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xB2 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xB3 */
                          { "LDY", LDY, ZAX, 2, 4, 1 },        /* 0xB4 */
                          { "LDA", LDA, ZAX, 2, 4, 1 },        /* 0xB5 */
                          { "LDX", LDX, ZAY, 2, 4, 1 },        /* 0xB6 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xB7 */
                          { "CLV", CLV, IMPL, 1, 2, 0 },       /* 0xB8 */
                          { "LDA", LDA, AY, 3, 4, 1 },         /* 0xB9 */
                          { "TSX", TSX, IMPL, 1, 2, 0 },       /* 0xBA */
                          { "", 0, 0, 0, 0, 0 },               /* 0xBB */
                          { "LDY", LDY, AX, 3, 4, 1 },         /* 0xBC */
                          { "LDA", LDA, AX, 3, 4, 1 },         /* 0xBD */
                          { "LDX", LDX, AY, 3, 4, 1 },         /* 0xBE */
                          { "", 0, 0, 0, 0, 0 },               /* 0xBF */
                          { "CPY", CPY, IMM, 2, 2, 0 },        /* 0xC0 */
                          { "CMP", CMP, IX, 2, 6, 1 },         /* 0xC1 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xC2 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xC3 */
                          { "CPY", CPY, ZABS, 2, 3, 1 },       /* 0xC4 */
                          { "CMP", CMP, ZABS, 2, 3, 1 },       /* 0xC5 */
                          { "DEC", DEC, ZABS, 2, 5, 3 },       /* 0xC6 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xC7 */
                          { "INY", INY, IMPL, 1, 2, 0 },       /* 0xC8 */
                          { "CMP", CMP, IMM, 2, 2, 0 },        /* 0xC9 */
                          { "DEX", DEX, IMPL, 1, 2, 0 },       /* 0xCA */
                          { "", 0, 0, 0, 0, 0 },               /* 0xCB */
                          { "CPY", CPY, ABS, 3, 4, 1 },        /* 0xCC */
                          { "CMP", CMP, ABS, 3, 4, 1 },        /* 0xCD */
                          { "DEC", DEC, ABS, 3, 6, 3 },        /* 0xCE */
                          { "", 0, 0, 0, 0, 0 },               /* 0xCF */
                          { "BNE", BNE, ABS, 2, 2, REL },      /* 0xD0 */
                          { "CMP", CMP, IY, 2, 5, 1 },         /* 0xD1 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xD2 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xD3 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xD4 */
                          { "CMP", CMP, ZAX, 2, 4, 1 },        /* 0xD5 */
                          { "DEC", DEC, ZAX, 2, 6, 3 },        /* 0xD6 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xD7 */
                          { "CLD", CLD, IMPL, 1, 2, 0 },       /* 0xD8 */
                          { "CMP", CMP, AY, 3, 4, 1 },         /* 0xD9 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xDA */
                          { "", 0, 0, 0, 0, 0 },               /* 0xDB */
                          { "", 0, 0, 0, 0, 0 },               /* 0xDC */
                          { "CMP", CMP, AX, 3, 4, 1 },         /* 0xDD */
                          { "DEC", DEC, AX, 3, 7, 3 },         /* 0xDE */
                          { "", 0, 0, 0, 0, 0 },               /* 0xDF */
                          { "CPX", CPX, IMM, 2, 2, 0 },        /* 0xE0 */
                          { "SBC", SBC, IX, 2, 6, 1 },         /* 0xE1 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xE2 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xE3 */
                          { "CPX", CPX, ZABS, 2, 3, 1 },       /* 0xE4 */
                          { "SBC", SBC, ZABS, 2, 3, 1 },       /* 0xE5 */
                          { "INC", INC, ZABS, 2, 5, 3 },       /* 0xE6 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xE7 */
                          { "INX", INX, IMPL, 1, 2, 0 },       /* 0xE8 */
                          { "SBC", SBC, IMM, 2, 2, 0 },        /* 0xE9 */
                          { "NOP", NOP, IMPL, 1, 2, 0 },       /* 0xEA */
                          { "", 0, 0, 0, 0, 0 },               /* 0xEB */
                          { "CPX", CPX, ABS, 3, 4, 1 },        /* 0xEC */
                          { "SBC", SBC, ABS, 3, 4, 1 },        /* 0xED */
                          { "INC", INC, ABS, 3, 6, 3 },        /* 0xEE */
                          { "", 0, 0, 0, 0, 0 },               /* 0xEF */
                          { "BEQ", BEQ, ABS, 2, 2, REL },      /* 0xF0 */
                          { "SBC", SBC, IY, 2, 5, 1 },         /* 0xF1 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xF2 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xF3 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xF4 */
                          { "SBC", SBC, ZAX, 2, 4, 1 },        /* 0xF5 */
                          { "INC", INC, ZAX, 2, 6, 3 },        /* 0xF6 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xF7 */
                          { "SED", SED, IMPL, 1, 2, 0 },       /* 0xF8 */
                          { "SBC", SBC, AY, 3, 4, 1 },         /* 0xF9 */
                          { "", 0, 0, 0, 0, 0 },               /* 0xFA */
                          { "", 0, 0, 0, 0, 0 },               /* 0xFB */
                          { "", 0, 0, 0, 0, 0 },               /* 0xFC */
                          { "SBC", SBC, AX, 3, 4, 1 },         /* 0xFD */
                          { "INC", INC, AX, 3, 7, 3 },         /* 0xFE */
                          { "", 0, 0, 0, 0, 0 }};              /* 0xFF */
