#ifndef MIPS_H
#define MIPS_H

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// register data structure
struct IFID {
	string instruction;
	int pc;
};

struct IDEX {
	int pc;
	int read_data1;
	int read_data2;
	int rs;
	int rt;
	int rd;
	int shamt;
	int funct;
	int offset;		// for I-type
	struct {
		int RegDst;
		int ALUOp0;
		int ALUOp1;
		int ALUSrc;
		int Branch;
		int MemRead;
		int MemWrite;
		int RegWrite;
		int MemToReg;
	} control;
};

struct EXMEM {
	int ALUresult;
	int WriteData;
	int zero;	// 1 for zero, 0 for not zero
	int PCSrc;	// branch control
	int ADDresult;
	int rd;
	struct {
		int Branch;
		int MemRead;
		int MemWrite;
		int RegWrite;
		int MemToReg;
	} control;
};

struct MEMWB {
	int ReadData;
	int ALUresult;
	int rd;
	struct {
		int RegWrite;
		int MemToReg;
	} control;
};


// variables
extern vector<string> instruction_set;
extern vector<int> registers;
extern vector<int> memory;
extern IFID ifid;
extern IDEX idex;
extern EXMEM exmem;
extern MEMWB memwb;
extern bool isIF;

// function definition
void Init_Registers();
void Init_Memory(int size);

void IF(string inst);
void ID();
bool EX();
bool MEM();
void WB();

// helper function
int btod(string n);

#endif
