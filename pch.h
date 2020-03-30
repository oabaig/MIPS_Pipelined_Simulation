// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

#ifndef PCH_H
#define PCH_H

#include <iostream>
#include <vector>
using namespace std;

// pipeline register data structure
struct IFID
{
	int Write;
	int pc;
	string instruction;
};

struct IDEX {
	int read_data1;
	int read_data2;
	int offset;
	int rs;
	int rt;
	int rd;
	int shamt;
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
	int ALUout;
	int WriteData;
	int address;
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

struct MEMWB {
	int ReadData;
	int ALUout;
	int address;
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


// variables
extern vector<string> instruction_set;
extern vector<int> registers;
extern vector<int> memory;
extern int inst_num;
extern IFID ifid;
extern IDEX idex;
extern EXMEM exmem;
extern MEMWB memwb;


// function definition
void Init_Registers();
void Init_Memory(int size);

void IF(string inst);
void ID();
void EX();
void MEM();
void WB();

// helper function
int btod(string n); 

#endif //PCH_H
