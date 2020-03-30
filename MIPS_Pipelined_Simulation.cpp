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
#include "mips_pipeline.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

// global variables
vector<string> instruction_set;
vector<int> registers;
vector<int> memory;
int inst_num;
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

	cout << "Registers\n";
	for (int i = 0; i < registers.size(); i++) {
		cout << "R" << i << " " << registers.at(i) << endl;
	}
	cout << "Memory\n";
	for (int i = 0; i < memory.size(); i++) {
		cout << i*4 << " " << memory.at(i) << endl;
	}
	cout << "Instruction Set\n";
	for (int i = 0; i < instruction_set.size(); i++) {
		cout << instruction_set.at(i) << endl;
	}

	return true;
}

int main() {
	Init_Registers();	// initialize register file to 0
	Init_Memory(5);	// initialize memory file 5*4 bytes

	string infilename = "input.txt";

	// read file
	read_file(infilename);

	return 0;
}
*/
