// pch.cpp: source file corresponding to pre-compiled header; necessary for compilation to succeed
#include "pch.h"
#include <string>
using namespace std;

void Init_Registers() {
	for (int i = 0; i < 10; i++) {
		registers.push_back(0);
	}
}

void Init_Memory(int size) {
	for (int i = 0; i < size; i++) {
		memory.push_back(0);
	}
}

void IF(string inst) {
	ifid.instruction = inst;
	ifid.pc += 4;
}

int ID() {
	// return 0 if need to stall
	// return 1 if successfully decode

	string inst = ifid.instruction;
	int RS = btod(inst.substr(6, 5));
	int RT = btod(inst.substr(11, 5));

	if (RS == idex.rt || RS == idex.rd || RT == idex.rt || RT == idex.rd) {
		// maybe saving some info about stall
		// might need a global variable to identify the stall start and stop
		return 0;
	}

	string opcode = inst.substr(0, 6);
	idex.read_data1 = btod(inst.substr(6, 5));
	idex.read_data2 = btod(inst.substr(11, 5));
	if (opcode == "000000") { // R-type
		idex.rs = btod(inst.substr(6, 5));
		idex.rt = btod(inst.substr(11, 5));
		idex.rd = btod(inst.substr(16, 5));
		idex.shamt = btod(inst.substr(21, 5));
		idex.funct = btod(inst.substr(26, 6));

		// initialize control for R-type
		idex.control.ALUSrc	= 1;
		idex.control.ALUSrc	= 0;
		idex.control.MemToReg	= 0;
		idex.control.RegWrite	= 1;
		idex.control.MemRead	= 0;
		idex.control.MemWrite	= 0;
		idex.control.Branch	= 0;
		idex.control.ALUOp0	= 1;
		idex.control.ALUOp1	= 0;

	}
	else { // I-type or J-type
		idex.rs = btod(inst.substr(6, 5));
		idex.rt = btod(inst.substr(11, 5));
		if (opcode == "100011") { // lw
			idex.offset = btod(inst.substr(16, 16));

			idex.control.ALUSrc	= 0;
			idex.control.ALUSrc	= 1;
			idex.control.MemToReg	= 1;
			idex.control.RegWrite	= 1;
			idex.control.MemRead	= 1;
			idex.control.MemWrite	= 0;
			idex.control.Branch	= 0;
			idex.control.ALUOp0	= 0;
			idex.control.ALUOp1	= 0;
		}
		else if (opcode == "101011") { // sw
			idex.offset = btod(inst.substr(16, 16));

			idex.control.ALUSrc	= 0;	// don't care
			idex.control.ALUSrc	= 1;
			idex.control.MemToReg	= 0;	// don't care
			idex.control.RegWrite	= 0;
			idex.control.MemRead	= 0;
			idex.control.MemWrite	= 1;
			idex.control.Branch	= 0;
			idex.control.ALUOp0	= 0;
			idex.control.ALUOp1	= 0;
		}
		else if (opcode == "000100") { // beq
			idex.offset = btod(inst.substr(6, 16));

			idex.control.ALUSrc	= 0;	// don't care
			idex.control.ALUSrc	= 0;
			idex.control.MemToReg	= 0;	// don't care
			idex.control.RegWrite	= 0;
			idex.control.MemRead	= 0;
			idex.control.MemWrite	= 0;
			idex.control.Branch	= 1;
			idex.control.ALUOp0	= 0;
			idex.control.ALUOp1	= 1;
		}
	}
	
	return 1;
}

// convert binary to decimal
int btod(string n) {
	int val = 0;
	for (int i = 0; i < n.size(); i++) {
		val += ((int)(n[i] - '0') * (pow(2.0, (double)(n.size() - i - 1))));
	}
	return val;
}
