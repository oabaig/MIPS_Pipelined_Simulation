#pragma once

#include<iostream>
#include<stdio.h>
#include<stdlib.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;

int memory[249]; // 996 memory locations. int is 4 bytes. 996 / 4 = 249

// create a struct for the R I J instruction types
// utilize bit fields so we don't have to waste memory
struct INSTRUCTION_SET {
	u8 opcode : 6;
	union { // use the same location in memory
		struct {
			u8 rs : 5;
			u8 rt : 5;
			u8 rd : 5;
			u8 shift : 5;
			u8 funct : 6;
		} r;
		struct {
			u8 rs : 5;
			u8 rt : 5;
			u16 imm;
		} i;
		struct {
			u32 addr : 24;
		} j;
	};
};

//registers 0 - 31 | 32 registers
struct REGISTERS {
	unsigned int R0;
	unsigned int R1;
	unsigned int R2;
	unsigned int R3;
	unsigned int R4;
	unsigned int R5;
	unsigned int R6;
	unsigned int R7;
	unsigned int R8;
	unsigned int R9;
	unsigned int R10;
	unsigned int R11;
	unsigned int R12;
	unsigned int R13;
	unsigned int R14;
	unsigned int R15;
	unsigned int R16;
	unsigned int R17;
	unsigned int R18;
	unsigned int R19;
	unsigned int R20;
	unsigned int R21;
	unsigned int R22;
	unsigned int R23;
	unsigned int R24;
	unsigned int R25;
	unsigned int R26;
	unsigned int R27;
	unsigned int R28;
	unsigned int R29;
	unsigned int R30;
	unsigned int R31;
};