#include <iostream>
#include <fstream>
#include "Lmachine.h"
using namespace std;
/*
--------------------------------------------------------------
|						虚拟机                               |
--------------------------------------------------------------
*/
//string 转char *
char * Lmachine::String2Char(string str)
{
	char *Cstr = (char*)str.data();
	return Cstr;
}
//默认无参数构造函数
Lmachine::Lmachine()
{

}
//初始化
bool Lmachine::Init()
{
	char  Judge;
	/*
	初始化
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
		ofstream fout(String2Char(OutFileName)); //新建输出文件
		if (fout)
			cout << "File "<<OutFileName<<" already  create success" << endl;
		return true;
	}
	else if (Judge == 'n' || Judge == 'N')
		return false;
	else
		return false;
}

//设定标志寄存器
void Lmachine::SetFlags(Bytes Register)
{
	Lcpu.Zero = (Register == 0);
	Lcpu.ProgramCounter = (Register <= 127);
}
//取得string类型token所对应的机器指令
Bytes Lmachine::Opcode(string token)
{
	Bytes Op = OpHALT;
	while (Op < MaxInstuction&&token != OpMemonic[Op])
		Op++;
	if (Op < MaxInstuction)
		return Op;
	else
		return OpError;//返回错误指令的代码
}
//计算变址地址 X+B
Bytes Lmachine::Index()
{
	return ((Memory[Lcpu.ProgramCounter] + Lcpu.Accumulator) % 256);
}
//执行加1操作
void Lmachine::Increment(Bytes & data)
{
	data = (data + 257) % 256;
}
//执行减1操作
void Lmachine::Decrement(Bytes & data)
{
	data = (data + 255) % 256;
}
//虚拟机执行内存中的汇编指令
void Lmachine::LmachineRun()
{
	Bytes ProgramValue;//保存PC的当前值
	Bytes Carry;//程序进位位的状态
	Lcpu.Carry = false;
	Lcpu.Zero = false;
	Lcpu.Sign = false;
	Lcpu.Accumulator = 0;
	Lcpu.IndexRegister = 0;
	Lcpu.BasePointer = 0;
	Lcpu.StackPointer = 0;
	Lcpu.ProgramCounter = 0;//程序开始位置
	LcpuStatus = Running;//CPU运行状态
	do
	{
		Lcpu.InstructionRegister = Memory[Lcpu.ProgramCounter];//从内存中取指令送入指令寄存器
		ProgramValue = Lcpu.ProgramCounter;
		Increment(Lcpu.ProgramCounter);//PC指向向一条将要执行的指令地址
		switch (Lcpu.InstructionRegister)
		{
		case OpHALT:	//CPU暂停指令 格式：HALT
			LcpuStatus = Finished;
			break;
		case OpCLEARAX:	//累加器清0
			Lcpu.Accumulator = 0;
			break;
		case OpClEARC:	//进位标志器清0
			Lcpu.Carry = 0;
			break;
		case OpCLEARI://变址寄存器清0
			Lcpu.IndexRegister = 0;
			break;
			//case OpINAXD:	//将10进制数写入累加器
			//case OpINAXB:	//将2进制数写入累加器
			//case OpINAXA:	//将ascii字符写入累加器
		case OpOUTAXD:	//将累加器数据以10进制形式输出
			if (Lcpu.Accumulator < 128)
			{
				ofstream fout(String2Char(OutFileName)); //打开文件
				fout << Lcpu.Accumulator; //写入文件
			}
			//case OpOUTAXB:	//将累加器数据以2进制形式输出
			//case OpOUTAXA:	//将累加器数据以ascii字符形式输出

		case OpINCAX://累加器加1，影响标志器
			Increment(Lcpu.Accumulator);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpDECAX://累加器减1，影响标志器
			Decrement(Lcpu.Accumulator);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpINCI://变址寄存器加1，影响标志器
			Increment(Lcpu.IndexRegister);
			SetFlags(Lcpu.IndexRegister);
			break;
		case OpDECI://变址寄存器减1，影响标志器
			Decrement(Lcpu.IndexRegister);
			SetFlags(Lcpu.IndexRegister);
			break;
		case OpAXTOI://累加器内容送入变址寄存器 x
			Lcpu.IndexRegister = Lcpu.Accumulator;
			break;
		case OpPUSH://压栈，堆栈指针减1，累加器的内容压入栈顶。
			Decrement(Lcpu.StackPointer);
			Memory[Lcpu.StackPointer] = Lcpu.Accumulator;
			break;
		case OpPOP://出栈，堆栈指针加1，将栈顶内容压入栈内
			Lcpu.Accumulator = Memory[Lcpu.StackPointer];
			Increment(Lcpu.StackPointer);
			Memory[Lcpu.StackPointer] = Lcpu.Accumulator;
			break;
		case OpLOADBAX://格式 LDA B ，将B地址单元中的内容送入累加器中，以当前PC所指内存的数值作为地址偏移
			Lcpu.Accumulator = Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpLOADIBAX://将变址寄存器+立即数B所指的内存单元的内容送入累加器 A=[I+B]
			Lcpu.Accumulator = Memory[Index()];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpLOADVBAX://将立即数B送入累加器
			Lcpu.Accumulator = Memory[Lcpu.ProgramCounter];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpLOADVBSP://将立即数B中的内容送到SP寄存器
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
			//加法
		case OpADDB://A=A+[B]
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Lcpu.ProgramCounter] > 255); //是否进位
			Lcpu.Accumulator = (Lcpu.Accumulator + Memory[Memory[Lcpu.ProgramCounter]]) % 256;//限定数值的大小
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpADDIB://A=A+[I+B]
			Lcpu.Carry = (Lcpu.Accumulator + Memory[Index()] > 255); //是否进位
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
		case OpADCB://A=A+C+[B] 带进位位
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
			//减法
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
			//比较
		case OpCMPB://A与[B]内容进行比较，影响标志位
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Memory[Lcpu.ProgramCounter]]);
			SetFlags((Lcpu.Accumulator - Memory[Memory[Lcpu.ProgramCounter]] + 256) % 256);
			Increment(Lcpu.ProgramCounter);
			break;
		case OpCMPIB://A与[B+I]内容进行比较，影响标志位
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Index()]);
			SetFlags((Lcpu.Accumulator - Memory[Index()] + 256) % 256);
			break;
		case OpCMPVB://A与B比较，影响标志位
			Lcpu.Carry = (Lcpu.Accumulator < Memory[Lcpu.ProgramCounter]);
			SetFlags((Lcpu.Accumulator - Memory[Lcpu.ProgramCounter] + 256) % 256);
			break;
			//与
		case OpANDB://A与[B]的内容位与，影响标志位
			Lcpu.Accumulator = Lcpu.Accumulator & Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			Lcpu.Carry = false;
			break;
		case OpANDVB://A与B位与，影响标志位
			Lcpu.Accumulator = Lcpu.Accumulator & Memory[Lcpu.ProgramCounter];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			Lcpu.Carry = false;
			break;
		case OpANDIB://A与[I+B]位与，影响标志位
			Lcpu.Accumulator = Lcpu.Accumulator & Memory[Index()];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			Lcpu.Carry = false;
			break;
			//或
		case OpORB://A与[B]的内容位或，影响标志位
			Lcpu.Accumulator = Lcpu.Accumulator | Memory[Memory[Lcpu.ProgramCounter]];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpORVB://A与B位或，影响标志位
			Lcpu.Accumulator = Lcpu.Accumulator | Memory[Lcpu.ProgramCounter];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
		case OpORIB://A与[I+B]位或，影响标志位
			Lcpu.Accumulator = Lcpu.Accumulator | Memory[Index()];
			Increment(Lcpu.ProgramCounter);
			SetFlags(Lcpu.Accumulator);
			break;
			//跳转
		case OpJMPB://跳转到B地址
			Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			break;
		case OpJZB://如果Z标志为1，跳转到B单元
			if (Lcpu.Zero == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJNZB://如果Z标志为0，跳转到B单元
			if (Lcpu.Zero == 0)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJSB://如果S标志为1，跳转到B单元
			if (Lcpu.Sign == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJNSB://如果S标志为0，跳转到B单元
			if (Lcpu.Sign == 0)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJC://如果C标志为1，跳转到B单元
			if (Lcpu.Carry == 1)
				Lcpu.ProgramCounter = Memory[Lcpu.ProgramCounter];
			else
				Increment(Lcpu.ProgramCounter);
			break;
		case OpJNC://如果C标志为0，跳转到B单元
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
//返回机器指令i的助记符,也就是汇编指令
string Lmachine::GetMemonic(int i)
{
	return  OpMemonic[i];
}