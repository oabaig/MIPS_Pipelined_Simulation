// MIPS_Pipelined_Simulation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "MIPS_Resources.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

void fileInput(ifstream &fpi, REGISTERS &R);

int main()
{
	string filename;
	ifstream fpi;
	REGISTERS R;

	cout << "Input the file name: ";
	cin >> filename;
	cout << endl;
	fpi.open(filename);
	fileInput(fpi, R);
}

void fileInput(ifstream &fpi, REGISTERS &R) {
	string line;
	string reg, memLoc, contents, code;

	getline(fpi, line);
	while (!fpi.eof()) {
		if (line == "REGISTERS") {
			while (line != "MEMORY") {
				getline(fpi, line);
				stringstream ss(line);
				ss >> reg >> contents;
				cout << reg << " " << contents << " || " << line << endl;
			}
		}
	}
	/*
	getline(fpi, inputText);
	while (!fpi.eof()) {

	//	if (inputText == "REGISTERS") {
			getline(fpi, inputText);
		//	while (inputText != "MEMORY") {
				//getline(fpi, inputText);
				temp << inputText;
				temp >> temp2;
				cout << temp2 << endl;
		//	}
	//	}
	}*/
}

/*
#include "mips.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// global variables
vector<string> instruction_set; // use program counter to step to next instruction
vector<int> registers;
vector<int> memory;
IFID ifid;
IDEX idex;
EXMEM exmem;
MEMWB memwb;

// read file and initialize regsiters & memory file
bool read_file(string filename) { 
	ifstream fin(filename);
	if (!fin.is_open()) {
		cout << "ERROR: file not open\n";
		return false;
	}

	string str;
	int num;
	bool regstart = false, memstart = false, codestart = false;
	while (fin >> str) {
		if (str == "REGISTERS") {
			regstart = true;
		}
		else if (str == "MEMORY") {
			regstart = false;
			memstart = true;
		}
		else if (str == "CODE") {
			memstart = false;
			codestart = true;
		}
		else if (regstart) {
			fin >> num;
			str.erase(0,1);
			registers.at(stoi(str)) = num;
		}
		else if (memstart) {
			fin >> num;
			memory.at((stoi(str) / 4)) = num;
		}
		else if (codestart) {
			instruction_set.push_back(str);
		}
	}
	fin.close();

	cout << "========== INPUT ==========\n";
	cout << "Registers\n";
	for (int i = 0; i < registers.size(); i++) {
		if(registers.at(i))
			cout << "R" << i << " " << registers.at(i) << endl;
	}
	cout << "Memory\n";
	for (int i = 0; i < memory.size(); i++) {
		if(memory.at(i))
			cout << i*4 << " " << memory.at(i) << endl;
	}
	cout << "Instruction Set\n";
	for (int i = 0; i < instruction_set.size(); i++) {
		cout << instruction_set.at(i) << endl;
	}
	cout << "===============================================\n";

	return true;
}

int main() {
	string infilename, outfilename;
	infilename = "input.txt";
	outfilename = "output.txt";

//	cout << "Enter input filename: ";
//	cin >> infilename;
//	cout << "Enter output filename: ";
//	cin >> outfilename;

	// initialization
	Init_Registers();	// initialize all register value to 0
	Init_Memory(5);		// initialize memory file 5*4 bytes

	// read file
	read_file(infilename);

	// output file
	ofstream fout(outfilename);

	// initialize program counter
	ifid.pc = 0;

	int cnt = 0, inst_num = 0;
	bool isMEM, isWB, branch;
	while (idex.pc < (instruction_set.size() * 4)) {
		// initialize
		inst_num = (ifid.pc / 4);
		isMEM = isWB = true;
		branch = false;

		// instructions
		IF(instruction_set.at(inst_num)); cnt++;
		cout << "C#" << cnt << " " << "I" << inst_num + 1 << "-IF" << endl;
		fout << "C#" << cnt << " " << "I" << inst_num + 1 << "-IF" << endl;
		ID(); cnt++;
		cout << "C#" << cnt << " " << "I" << inst_num + 1 << "-ID" << endl;
		fout << "C#" << cnt << " " << "I" << inst_num + 1 << "-ID" << endl;
		isMEM = EX(); cnt++;
		cout << "C#" << cnt << " " << "I" << inst_num + 1 << "-EX" << endl;
		fout << "C#" << cnt << " " << "I" << inst_num + 1 << "-EX" << endl;
		if (isMEM) {
			isWB = MEM(); cnt++;
			cout << "C#" << cnt << " " << "I" << inst_num + 1 << "-MEM" << endl;
			fout << "C#" << cnt << " " << "I" << inst_num + 1 << "-MEM" << endl;
		}
		isWB = MEM();
		if (isWB) {
			WB(); cnt++;
			cout << "C#" << cnt << " " << "I" << inst_num + 1 << "-WB" << endl;
			fout << "C#" << cnt << " " << "I" << inst_num + 1 << "-WB" << endl;
		}
	}
	cout << "=========== FINAL OUTPUT ===========\n";
	cout << "Registers\n";
	fout << "Registers\n";
	for (int i = 0; i < registers.size(); i++) {
		if (registers.at(i)) {
			cout << "R" << i << " " << registers.at(i) << endl;
			fout << "R" << i << " " << registers.at(i) << endl;
		}
	}
	cout << "Memory\n";
	fout << "Memory\n";
	for (int i = 0; i < memory.size(); i++) {
		if (memory.at(i)) {
			cout << i * 4 << " " << memory.at(i) << endl;
			fout << i * 4 << " " << memory.at(i) << endl;
		}
	}
	
	fout.close();
	return 0;
}
*/
