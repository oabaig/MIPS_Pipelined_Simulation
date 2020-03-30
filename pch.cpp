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

void ID() {
//	string inst = instruction_set.at(inst_num);
	string inst = ifid.instruction;
	string opcode, funct;
	opcode = inst.substr(0, 6);
	if (opcode == "000000") {	// R-type
		funct = inst.substr(26, 6);
		idex.rs = btod(inst.substr(6, 5));
		idex.rt = btod(inst.substr(11, 5));
		idex.rd = btod(inst.substr(16, 5));
		idex.shamt = btod(inst.substr(21, 5));

		// seperate by funct
		if (funct == "100000") { // add

		}
		else if (funct == "100010") { // sub

		}
	}
	else { // I-type or J-type

		if (opcode == "100011") { // lw

		}
		else if (opcode == "101011") { // sw

		}


	}
}

// convert binary to decimal
int btod(string n) {
	int val = 0;
	for (int i = 0; i < n.size(); i++) {
		val += ((int)(n[i] - '0') * (pow(2.0, (double)(n.size() - i - 1))));
	}
	return val;
}
