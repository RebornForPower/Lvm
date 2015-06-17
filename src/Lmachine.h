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
	/*
	数据成员
	*/
	ofstream Ofile;//定义输出文件
	string OutFileName;//输出结果的文件名
	string CodeFileName;//需要打开的代码文件名
	CPU Lcpu;//虚拟机的CPU
	Status LcpuStatus;//虚拟机CPU的运行状态
	Bytes Memory[MemSize];//虚拟机内存空间
	LmachineError LError;//虚拟机类型
	LmachineEndStatus LendStatus;//虚拟机结束时的状态
	/*
	成员函数
	*/
	char * String2Char(string str);//string 转char *
	Lmachine();//默认无参构造函数
	bool Init();//初始化，以及开始欢迎界面 及用户选项输入,初始化成功返回true，否则返回flase
	string GetMemonic(int i); //返回机器指令i的助记符，也就是汇编指令
	void LmachineRun();//执行程序
	void Increment(Bytes &data);//执行加1操作
	void Decrement(Bytes &data);//执行减1操作
	void SetFlags(Bytes Register);//根据寄存器的值设定标志器
	void PrintRunError();//输出程序运行的错误
	Bytes Index();//计算变址地址 AX+B
	Bytes Opcode(string token);//取得string类型token所对应的机器指令
	void LmachineQuit();//退出虚拟机
};