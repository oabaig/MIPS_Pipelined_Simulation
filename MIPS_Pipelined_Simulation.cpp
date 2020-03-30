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