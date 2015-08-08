#pragma once
#include "Global.h"
#include "Assembler.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

//虚拟机
class Lmachine
{
public:
	
	ofstream Ofile;
	string OutFileName;//输出文件的文件名
	string CodeFileName;//需要打开的代码文件名
	CPU Lcpu;//虚拟机的CPU
	Status LcpuStatus;
	Bytes Memory[MemSize];
	LmachineError LError;
	LmachineEndStatus LendStatus;

	char * String2Char(string str);
	Lmachine();
	bool Init();
	string GetMemonic(int num);
	void LmachineRun();
	void Increment(Bytes &data);
	void Decrement(Bytes &data);
	void SetFlags(Bytes Register);
	void PrintRunError();
	Bytes Index();
	Bytes Opcode(string token);
	void LmachineQuit();
};