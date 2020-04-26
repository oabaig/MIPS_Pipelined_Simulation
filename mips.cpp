#include "mips.h"
#include <iostream>
using namespace std;

bool isBEQ, isBNE;

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

void ID() {
	string inst = ifid.instruction;
	idex.pc = ifid.pc;
	
	isBNE = false;
	isBEQ = false;

	string opcode = inst.substr(0, 6);
	if (opcode == "000000") {	// R-type
		// initialize control for R-type
		idex.control.RegDst = 1;
		idex.control.ALUSrc = 0;
		idex.control.MemToReg = 0;
		idex.control.RegWrite = 1;
		idex.control.MemRead = 0;
		idex.control.MemWrite = 0;
		idex.control.Branch = 0;
		idex.control.ALUOp0 = 1;
		idex.control.ALUOp1 = 0;
	}
	else { // I-type
		if (opcode == "100011") { // lw
			idex.control.RegDst = 0;
			idex.control.ALUSrc = 1;
			idex.control.MemToReg = 1;
			idex.control.RegWrite = 1;
			idex.control.MemRead = 1;
			idex.control.MemWrite = 0;
			idex.control.Branch = 0;
			idex.control.ALUOp0 = 0;
			idex.control.ALUOp1 = 0;
		}
		else if (opcode == "101011") { // sw
			idex.control.RegDst = 0;	// don't care
			idex.control.ALUSrc = 1;
			idex.control.MemToReg = 0;	// don't care
			idex.control.RegWrite = 0;
			idex.control.MemRead = 0;
			idex.control.MemWrite = 1;
			idex.control.Branch = 0;
			idex.control.ALUOp0 = 0;
			idex.control.ALUOp1 = 0;
		}
		else if (opcode == "001000") { // addi
			idex.control.RegDst = 0;
			idex.control.ALUSrc = 1;
			idex.control.MemToReg = 0;
			idex.control.RegWrite = 1;
			idex.control.MemRead = 0;
			idex.control.MemWrite = 0;
			idex.control.Branch = 0;
			idex.control.ALUOp0 = 0;
			idex.control.ALUOp1 = 0;
		}
		else if (opcode == "000100") { // beq
			isBEQ = true;
			idex.control.RegDst = 0;	// don't care
			idex.control.ALUSrc = 0;
			idex.control.MemToReg = 0;	// don't care
			idex.control.RegWrite = 0;
			idex.control.MemRead = 0;
			idex.control.MemWrite = 0;
			idex.control.Branch = 1;
			idex.control.ALUOp0 = 0;
			idex.control.ALUOp1 = 1;
		}
		else if (opcode == "000101") { // bne
			isBNE = true;
			idex.control.RegDst = 0;	// don't care
			idex.control.ALUSrc = 0;
			idex.control.MemToReg = 0;	// don't care
			idex.control.RegWrite = 0;
			idex.control.MemRead = 0;
			idex.control.MemWrite = 0;
			idex.control.Branch = 1;
			idex.control.ALUOp0 = 0;
			idex.control.ALUOp1 = 1;
		}
	}

	// register file
	idex.rs = btod(inst.substr(6, 5));
	idex.rt = btod(inst.substr(11, 5));
	if (idex.control.RegDst)
		idex.rd = btod(inst.substr(16, 5));
	else
		idex.rd = idex.rt;
	idex.read_data1 = registers.at(idex.rs);
	idex.read_data2 = registers.at(idex.rt);

	// data
	idex.shamt = btod(inst.substr(21, 5));
	idex.funct = btod(inst.substr(26, 6));
	idex.offset = btod(inst.substr(16, 16));
}

bool EX() {
	int ALU_A, ALU_B; // 2 value going into ALU

	ALU_A = idex.read_data1;
	if (idex.control.ALUSrc)
		ALU_B = idex.offset;
	else
		ALU_B = idex.read_data2;

	string ALUcontrol; // 4-bit

	if (idex.control.ALUOp0 == 0 && idex.control.ALUOp1 == 0) { // lw & sw
		ALUcontrol = "0010"; // add
	}
	else if (idex.control.ALUOp0 == 0 && idex.control.ALUOp1 == 1) {// beq bne
		ALUcontrol = "0110"; // sub
	}
	else if (idex.control.ALUOp0 == 1 && idex.control.ALUOp1 == 0) { // R-type
		if (idex.funct == 32 || idex.funct == 33)
			ALUcontrol = "0010"; // add
		if (idex.funct == 34 || idex.funct == 35)
			ALUcontrol = "0110"; // sub
		if (idex.funct == 36)
			ALUcontrol = "0000"; // and
		if (idex.funct == 37)
			ALUcontrol = "0001"; // or
	}

	// carry over controls
	exmem.control.Branch = idex.control.Branch;
	exmem.control.MemRead = idex.control.MemRead;
	exmem.control.MemWrite = idex.control.MemWrite;
	exmem.control.RegWrite = idex.control.RegWrite;
	exmem.control.MemToReg = idex.control.MemToReg;

	exmem.WriteData = idex.read_data2;
	exmem.rd = idex.rd;

	// add for pc
	exmem.ADDresult = idex.pc + idex.offset * 4;

	// operations
	exmem.zero = 0;
	if (ALUcontrol == "0010") // add
		exmem.ALUresult = ALU_A + ALU_B;
	else if (ALUcontrol == "0110") { // sub
		exmem.ALUresult = ALU_A - ALU_B;
		if (exmem.ALUresult == 0)
			exmem.zero = 1;
		else
			exmem.zero = 0;
	}
	else if (ALUcontrol == "0000") // and
		exmem.ALUresult = ALU_A & ALU_B;
	else if (ALUcontrol == "0001") // or
		exmem.ALUresult = ALU_A | ALU_B;

	// beq bne pc control
	exmem.PCSrc = 0;
	if (isBEQ) {
		if (exmem.zero)
			exmem.PCSrc = 1;
		else
			exmem.PCSrc = 0;
	}
	else if (isBNE){
		if (exmem.zero)
			exmem.PCSrc = 0;
		else
			exmem.PCSrc = 1;
	}
	exmem.PCSrc &= exmem.control.Branch;

	// branch
	if (exmem.PCSrc)
		ifid.pc = exmem.ADDresult;

	// return true for if continue to MEM()
	// else false
	if (exmem.control.MemRead || exmem.control.MemWrite || exmem.control.MemToReg)
		return true;
	else {
		memwb.control.MemToReg = exmem.control.MemToReg;
		memwb.control.RegWrite = exmem.control.RegWrite;
		memwb.ALUresult = exmem.ALUresult;
		memwb.rd = exmem.rd;
		return false;
	}
}

bool MEM() {
	// memory file
	if (exmem.control.MemRead) // lw
		memwb.ReadData = memory.at(exmem.ALUresult / 4);
	if (exmem.control.MemWrite) // sw
		memory.at(exmem.ALUresult / 4) = exmem.WriteData;

	// carry over
	memwb.control.MemToReg = exmem.control.MemToReg;
	memwb.control.RegWrite = exmem.control.RegWrite;
	memwb.ALUresult = exmem.ALUresult;
	memwb.rd = exmem.rd;

	// return true for if continue to WB()
	// else false
	if (exmem.control.RegWrite)
		return true;
	else
		return false;
}


void WB() {
	if (memwb.control.RegWrite) {
		if (memwb.control.MemToReg)
			registers.at(memwb.rd) = memwb.ReadData;
		else
			registers.at(memwb.rd) = memwb.ALUresult;
	}
}


// helper function
// convert binary to decimal
int btod(string n) {
	int val = 0;
	for (int i = 0; i < n.size(); i++) {
		val += ((int)(n[i] - '0') * (pow(2.0, (double)(n.size() - i - 1))));
	}
	return val;
}
