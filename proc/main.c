#include <stdio.h>
#include <string.h>

#include "datatype.h"
#include "memory.h"

#define VERSION "0.1.1"

// INSTRUCTIONS - OPCODES (BASIC)
#define NOP 0x00
#define HALT 0xFF

//ARITHMETIC LOGIC UNIT COMMANDS
#define SUM 0x00
#define SUB 0x01
#define MUL 0x02
#define DIV 0x03
#define OR 0x04
#define AND 0x05
#define XOR 0x06
#define NOT 0x07

enStage stage = RESET;

// GENERAL REGISTERS
uint16_t PC; //Program Counter
uint8_t IR; //Instruction Register
uint8_t LI; //Last Instruction
uint16_t SP; //Stack Pointer
uint16_t IX; //Index Register
uint16_t IY; //Index Register
uint8_t REG[8]; //General Registers
uint8_t VOL[8]; //Volatile Registers
uint8_t REG_F; //Flags Register

#define REG_A REG[0x07]
#define VOL_A VOL[0x07]
#define REG_B REG[0x00]
#define VOL_B REG[0x00]
#define REG_C REG[0x01]
#define VOL_C VOL[0x01]
#define REG_D REG[0x02]
#define VOL_D VOL[0x02]
#define REG_E REG[0x03]
#define VOL_E VOL[0x03]
#define REG_H REG[0x04]
#define VOL_H VOL[0x04]
#define REG_L REG[0x05]
#define VOL_L VOL[0x05]

#define FLAG REG_F
#define FLG_C (FLAG & 0x01)
#define SET_C FLAG |= 0x01
#define CLR_C FLAG &= ~0x01
#define FLG_N ((FLAG >> 1) & 0x01)
#define SET_N FLAG |= 0x02 
#define CLR_N FLAG &= ~0x02
#define FLG_P ((FLAG >> 2) & 0x01)
#define SET_P FLAG |= 0x03
#define CLR_P FLAG &= ~0x03
#define FLG_H ((FLAG >> 3) & 0x01)
#define SET_H FLAG |= 0x04
#define CLR_H FLAG &= ~0x04
#define FLG_Z ((FLAG >> 5) & 0x01)
#define SET_Z FLAG |= 0x06
#define CLR_Z FLAG &= ~0x06
#define FLG_S ((FLAG >> 6) & 0x01)
#define SET_S FLAG |= 0x07
#define CLR_S FLAG &= ~0x07

// MEMORY REGISTERS
uint16_t MAR; //Memory Address Register
uint8_t MDR; //Memory Data Register

// ARITHMETIC LOGIC UNIT
uint8_t UI1; //ALU Input Register #1
uint8_t UI2; //ALU Input Register #2
uint8_t UO; //ALU Output Register
uint8_t ALU; //ALU Operation Register

//JUST FOR DEBUG, SHOULD BE REMOVED LATER!
char opcodename[3];

void ALUWork() {
	switch (ALU) {
		case SUM: {
			if (((UI1 >> 3) & 0x01) && ((UI2 >> 3) & 0x01)) {
				SET_H;
			} else {
				CLR_H;
			}
			if (((UI1 >> 7) & 0x01) && ((UI2 >> 7) & 0x01)) {
				SET_C;
				SET_P;
			} else {
				CLR_C;
				CLR_P;
			}
			UO = UI1 + UI2;
			if ((UO >> 7) & 0x01) {
				SET_S;
			} else {
				CLR_S;
			}
			if (UO == 0) {
				SET_Z;
			} else {
				CLR_Z;
			}
			CLR_N;
			break;
		}
		case SUB: {
			UO = UI1 - UI2;
			break;
		}
		case MUL: {
			UO = UI1 * UI2;
			break;
		}
		case DIV: {
			UO = UI1 / UI2;
			break;
		}
		case OR: {
			UO = UI1 | UI2;
			break;
		}
		case AND: {
			UO = UI1 & UI2;
			break;
		}
		case XOR: {
			UO = UI1 ^ UI2;
			break;
		}
	}
}

int main(int argc, char *argv[]) {
	int PROC_RUN = 1;
	int MUST_SAVE = 0;
	//int STEP = 0;
	int HANDLED = 0;
	opcodename[3] = '\0';
	while (PROC_RUN) {
		printf("Stage: ");
		HANDLED = 0;
		switch (stage) {
			case FETCH: {
				printf("FETCH\r\n");
				MAR = PC;
				PC++;
				MDR = ReadROM(MAR, HALT);
				stage = DECODE;
				break;
			}
			case DECODE: {
				printf("DECODE\r\n");
				if (MUST_SAVE) {
					MUST_SAVE = 0;
					LI = IR;
				}
				IR = MDR;
				if (LI == 0xCE) { //ADC A, n
					ALU = SUM;
					UI1 = REG_A;
					UI2 = IR;
					ALUWork();
					HANDLED = 1;
				} else if (LI == 0xC6) { //ADD A, n
					ALU = SUM;
					UI1 = REG_A;
					UI2 = IR;
					ALUWork();
					HANDLED = 1;
				}
				if (!HANDLED) {
					if((IR >> 3) == 0x10) { //ADD A, r
						memcpy(opcodename, "ADD", 3);
						ALU = SUM;
						UI1 = REG_A;
						UI2 = REG[(IR & 0x07)];
						ALUWork();
					} else if((IR >> 3) == 0x11) { //ADC A, r
						memcpy(opcodename, "ADC", 3);
						ALU = SUM;
						UI1 = REG_A;
						UI2 = REG[(IR & 0x07)];
						ALUWork();
					} else if ((IR >> 3) == 0xCE) { //ADC A, n
						MUST_SAVE = 1;
					} else if (IR == 0x8E) { // ADC A, (HL)
						ALU = SUM;
						UI1 = REG_A;
						IX = (REG_H << 8);
						IX &= REG_L;
						UI2 = ReadRAM(IX, 0x00);
						ALUWork();
					}
				}
				stage = EXECUTE;
                break;
			}
			case EXECUTE: {
				printf("EXECUTE\r\n");
				if (LI == 0xCE) { //ADC A, n
					REG_A = UO;
					HANDLED = 1;
				} else if (LI == 0xC6) { //ADD A, n
					REG_A = UO;
					HANDLED = 1;
				}
				if (!HANDLED) {
					if (IR == NOP) {
						memcpy(opcodename, "NOP", 3);
						//NO OPERATION.
					} else if ((IR >> 3) == 0x10) { //ADD A, r
						memcpy(opcodename, "ADD", 3);
						REG_A = UO;
					} else if ((IR >> 3) == 0x11) { //ADC A, r
						memcpy(opcodename, "ADC", 3);
						REG_A = UO;
					} else if (IR == 0x8E) { //ADC A, (HL)
						memcpy(opcodename, "ADC", 3);
						REG_A = UO;
					} else if(IR == HALT) {
						memcpy(opcodename, "HLT", 3);
						stage = HALT;
					}
				} else {
					LI = NOP;
				}
				if (stage == EXECUTE) {
					stage = FETCH;
				}
				break;
			}
			case HALT:
				PROC_RUN = 0;
				break;
			case RESET:
			default: {
				printf("RESET\r\n");
				CreateRAM();
				PC = 0;
				IR = NOP;
				LI = NOP;
				SP = 0;
				stage = FETCH;
			}
		}
		printf("REGISTERS\r\n");
		printf("  OPC: %s\r\n", opcodename);
		printf("  MAR: %u\r\n", MAR);
		printf("  MDR: %u\r\n", MDR);
		printf("  IR: %u\r\n", IR);
		printf("  PC: %u\r\n", PC);
		printf("  UO: %u\r\n", UO);
		printf("press any key to continue..");
		getchar();
	}
	printf("press any key to continue..");
	getchar();
}
