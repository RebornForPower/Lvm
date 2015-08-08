#include <iostream>
#include <fstream>
#include "Lmachine.h"
using namespace std;
/*
--------------------------------------------------------------
|						虚拟机                                |
--------------------------------------------------------------
*/
//string תchar *
char * Lmachine::String2Char(string str)
{
	char *Cstr = (char*)str.data();
	return Cstr;
}
//
Lmachine::Lmachine()
{

}
//
bool Lmachine::Init()
{
	char  Judge;
	/*
	
	*/
	cout << "--------------------------------------" << endl;
	cout << "|         welcome to Lmachine        |" << endl;
	cout << "|                                    |" << endl;
	cout << "|                                    |" << endl;
	cout << "|                    By: Leviathan   |" << endl;
	cout << "--------------------------------------" << endl;
	cout << "Please input code file name  :  ";
	cin >> CodeFileName;
	cout << "Please input Output file name : ";
	cin >> OutFileName;
	cout << "Continue ? y/n :   ";
	cin >> Judge;
	while (Judge != 'y' && Judge != 'Y' && Judge != 'n' && Judge != 'N')
	{
		cout << "Please input correct choice" << endl;
		cin >> Judge;
	}
	if (Judge == 'y' || Judge == 'Y')
	{
		ofstream fout(String2Char(OutFileName)); //
		if (fout)
			cout << "File "<<OutFileName<<" already  create success" << endl;
		return true;
	}
	else if (Judge == 'n' || Judge == 'N')
		return false;
	else
		return false;
}

//
void Lmachine::SetFlags(Bytes Register)
{
	Lcpu.Zero = (Register == 0);
	Lcpu.ProgramCounter = (Register <= 127);
}
//
Bytes Lmachine::Opcode(string token)
{
	Bytes Op = OpHALT;
	while (Op < MaxInstuction&&token != OpMemonic[Op])
		Op++;
	if (Op < MaxInstuction)
		return Op;
	else
		return OpError;//
}
// X+B
Bytes Lmachine::Index()
{
	return ((Memory[Lcpu.ProgramCounter] + Lcpu.Accumulator) % 256);
}
//
void Lmachine::Increment(Bytes & data)
{
	data = (data + 257) % 256;
}
//
void Lmachine::Decrement(Bytes & data)
{
	data = (data + 255) % 256;
}
//
void Lmachine::LmachineRun()
{
	Bytes ProgramValue;//
	Bytes Carry;//
	Lcpu.Carry = false;
	Lcpu.Zero = false;
	Lcpu.Sign = false;
	Lcpu.Accumulator = 0;
	Lcpu.IndexRegister = 0;
	Lcpu.BasePointer = 0;
	Lcpu.StackPointer = 0;
	Lcpu.ProgramCounter = 0;//
	LcpuStatus = Running;//
	do
	{
		Lcpu.InstructionRegister = Memory[Lcpu.ProgramCounter];//
		ProgramValue = Lcpu.ProgramCounter;
		Increment(Lcpu.ProgramCounter);//
		switch (Lcpu.InstructionRegister)
		{
		case OpHALT:	// 
			LcpuStatus = Finished;
			break;
		case OpCLEARAX:	//
			Lcpu.Accumulator = 0;
			break;
		case OpClEARC:	//
			Lcpu.Carry = 0;
			break;
		case OpCLEARI://��ַ�Ĵ�����0
			Lcpu.IndexRegister = 0;
			break;
			//case OpINAXD:	
			//case OpINAXB:	
			//case OpINAXA:	
		case OpOUTAXD:	//
			if (Lcpu.Accumulator < 128)
			{
				ofstream fout(String2Char(OutFileName)); //
				fout << Lcpu.Accumulator; //
			}
			//case OpOUTAXB:
			//case OpOUTAXA:

		case OpINCAX:
			Increment(Lcpu.Accumulator);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpDECAX:
			Decrement(Lcpu.Accumulator);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpINCI:
			Increment(Lcpu.IndexRegister);
			SetFlags(Lcpu.IndexRegister);
			break;
		case OpDECI:
			Decrement(Lcpu.IndexRegister);
			SetFlags(Lcpu.IndexRegister);
			break;
		case OpAXTOI:
			Lcpu.IndexRegister = Lcpu.Accumulator;
			break;
		case OpPUSH:
			Decrement(Lcpu.StackPointer);
			Memory[Lcpu.StackPointer] = Lcpu.Accumulator;
			break;
		case OpPOP:
			Lcpu.Accumulator = Memory[Lcpu.StackPointer];
			Increment(Lcpu.StackPointer);
			Memory[Lcpu.StackPointer] = Lcpu.Accumulator;
			break;
		case OpLOADBAX:
			Lcpu.Accumulator = Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpLOADIBAX:
			Lcpu.Accumulator = Memory[Index()];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpLOADVBAX:
			Lcpu.Accumulator = Memory[Lcpu.ProgramCounter];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpLOADVBSP:
			Lcpu.StackPointer = Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			break;
		case OpSTOREAXB://[B]=A
			Memory[Memory[Lcpu.ProgramCounter]] = Lcpu.Accumulator;
			Increment(Lcpu.ProgramCounter);
			break;
		case OpSIOREAXBI://[B+I]=A
			Memory[Index()] = Lcpu.Accumulator;
			Increment(Lcpu.Accumulator);
			break;
			//
		case OpADDB://A=A+[B]
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Lcpu.ProgramCounter] > 255); //
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Memory[Lcpu.ProgramCounter]]) % 256;//
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpADDIB://A=A+[I+B]
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Index()] > 255); //
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Index()]) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpADDVB://A=A+B
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Lcpu.ProgramCounter]) > 255;
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Lcpu.ProgramCounter]) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpADCB:
			Carry = Lcpu.Carry;
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Memory[Lcpu.ProgramCounter]] + Carry) > 255;
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Memory[Lcpu.ProgramCounter]] + Carry) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpADCIB://A=A+C+[I+B]
			Carry = Lcpu.Carry;
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Index()] + Carry) > 255;
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Index()] + Carry) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpADCVB://A=A+C+B
			Carry = Lcpu.Carry;
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Lcpu.ProgramCounter] + Carry) > 255;
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Lcpu.ProgramCounter] + Carry) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
			//
		case OpSUBB://A=A-[B]
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Memory[Lcpu.ProgramCounter]]);
			Lcpu.Accumulator = (Lcpu.Accumulator - Memory[Memory[Lcpu.ProgramCounter]] + 256) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpSUBIB://A=A-[I+B]
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Index()]);
			Lcpu.Accumulator = (Lcpu.Accumulator - Memory[Index()] + 256) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpSUBVB://A=A-B
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Lcpu.ProgramCounter]);
			Lcpu.Accumulator = (Lcpu.Accumulator - Memory[Lcpu.ProgramCounter] + 256) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpSBCB://A=A-C-[B]
			Carry = Lcpu.Carry;
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Memory[Lcpu.ProgramCounter]] + Carry);
			Lcpu.Accumulator = (Lcpu.Accumulator - Carry - Memory[Memory[Lcpu.ProgramCounter]] + 256) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpSBCIB://A=A-C-[I+B]
			Carry = Lcpu.Carry;
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Index()] + Carry);
			Lcpu.Accumulator = (Lcpu.Accumulator - Carry - Memory[Index()] + 256) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpSBCVB://A=A-C-B
			Carry = Lcpu.Carry;
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Lcpu.ProgramCounter] + Carry);
			Lcpu.Accumulator = (Lcpu.Accumulator - Carry - Memory[Lcpu.ProgramCounter] + 256) % 256;
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
			//
		case OpCMPB:
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Memory[Lcpu.ProgramCounter]]);
			SetFlags((Lcpu.Accumulator - Memory[Memory[Lcpu.ProgramCounter]] + 256) % 256);
			Increment(Lcpu.ProgramCounter);
			break;
		case OpCMPIB:
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Index()]);
			SetFlags((Lcpu.Accumulator - Memory[Index()] + 256) % 256);
			break;
		case OpCMPVB://A��B�Ƚϣ�Ӱ����־λ
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Lcpu.ProgramCounter]);
			SetFlags((Lcpu.Accumulator - Memory[Lcpu.ProgramCounter] + 256) % 256);
			break;
			//
		case OpANDB:
			Lcpu.Accumulator = Lcpu.Accumulator & Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			Lcpu.Carry = false;
			break;
		case OpANDVB:
			Lcpu.Accumulator = Lcpu.Accumulator & Memory[Lcpu.ProgramCounter];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			Lcpu.Carry = false;
			break;
		case OpANDIB:
			Lcpu.Accumulator = Lcpu.Accumulator & Memory[Index()];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			Lcpu.Carry = false;
			break;
			
		case OpORB:
			Lcpu.Accumulator = Lcpu.Accumulator | Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpORVB:
			Lcpu.Accumulator = Lcpu.Accumulator | Memory[Lcpu.ProgramCounter];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpORIB:
			Lcpu.Accumulator = Lcpu.Accumulator | Memory[Index()];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
			
		case OpJMPB:
			Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			break;
		case OpJZB:
			if (Lcpu.Zero == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJNZB:
			if (Lcpu.Zero == 0)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJSB:
			if (Lcpu.Sign == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJNSB:
			if (Lcpu.Sign == 0)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJC:
			if (Lcpu.Carry == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJNC:
			if (Lcpu.Carry == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		default:
			break;
		}
	} while (LcpuStatus == Running);
	if (LcpuStatus == Finished&&LError == NoneError)
		LendStatus = Success;
	else
		LendStatus = Failed;

}

string Lmachine::GetMemonic(int i)
{
	return  OpMemonic[i];
}