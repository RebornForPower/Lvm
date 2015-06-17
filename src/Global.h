#pragma once

#include <string>
#include <boost/regex.hpp>
using namespace std;

static boost::regex Regex("([0-9]+)|([A-Z_a-z]*[A-Z_a-z0-9]+)|(:)|(;.*)"); //正则表达式
static boost::smatch what;
typedef unsigned char Bytes; //一个字节
#define MemSize 256 //虚拟机内存
#define MaxInstuction 51 //汇编指令数目
//同名引用结点
struct SymbolReferenceNode
{
	Bytes ReferenceAddr;	   //同名引用的符号的内存地址
	SymbolReferenceNode * Next;//下一个同名引用的结点
};
//符号定义
struct Symbol
{
	std::string SymbolName;//符号名字
	Bytes SymbolAddr;	//符号内存地址
	SymbolReferenceNode * First;//该符号首次出现
};
//CPU设计
struct CPU
{
	Bytes Accumulator;//累加器,简称AX
	Bytes StackPointer;//堆栈指针SP，简称SP
	Bytes IndexRegister;//变址寄存器，简称I
	Bytes InstructionRegister;//指令寄存器，简称IR
	Bytes ProgramCounter;//程序计数器，简称PC
	Bytes BasePointer;//基址指针，简称BP
	bool Carry;//进位标志器，简称C
	bool Zero;//运算结果是否为0，结果为0，Z=1
	bool Sign;//符号标志，结果为负时，S=1
};
//虚拟机的运行状态
enum Status
{
	Running,
	Finished,
};
//虚拟机错误类型
enum LmachineError
{
	NoneError,
	OperandError,
	DataError,
};
//虚拟机运行结束状态
enum LmachineEndStatus
{
	Success,//运行成功
	Failed,//运行失败
};
//字符流类型
enum TokenType
{
	ASMCode,
	Lablel,
	ReferLabel,
	Number,
	ID,
	UnKnown
};
//虚拟机机器指令表
enum Operand
{
	/*
	!!!!注意：B 代表立即数，前面加V 代表立即数本身  不加V代表[B] 即B地址单元中的内容
	*/
	OpHALT,	//CPU暂停指令 格式：HALT
	OpCLEARAX,		//累加器清0
	OpClEARC,	//进位标志器清0
	OpCLEARI,//变址寄存器清0
	OpINAXD,	//将10进制数写入累加器
	OpINAXB,	//将2进制数写入累加器
	OpINAXA,	//将ascii字符写入累加器
	OpOUTAXD,	//将累加器数据以10进制形式输出
	OpOUTAXB,	//将累加器数据以2进制形式输出
	OpOUTAXA,	//将累加器数据以ascii字符形式输出
	OpINCAX,//累加器加1，影响标志器
	OpDECAX,//累加器减1，影响标志器
	OpINCI,//变址寄存器加1，影响标志器
	OpDECI,//变址寄存器减1，影响标志器
	OpAXTOI,//累加器内容送入变址寄存器 x
	OpPUSH,//压栈，堆栈指针减1，累加器的内容压入栈顶。
	OpPOP,//出栈，堆栈指针加1，将栈顶内容压入栈内
	OpLOADBAX,//格式 LDA B ，将B地址单元中的内容送入累加器中，以当前PC所指内存的数值作为地址偏移
	OpLOADIBAX,//将变址寄存器+立即数B所指的内存单元的内容送入累加器 A=[I+B]
	OpLOADVBAX,//将立即数B送入累加器
	OpLOADVBSP,//将立即数B中的内容送到SP寄存器
	OpSTOREAXB,//[B]=A
	OpSIOREAXBI,//[B+I]=A
	//加法
	OpADDB,//A=A+[B]
	OpADDIB,//A=A+[I+B]
	OpADDVB,//A=A+B
	OpADCB,//A=A+C+[B]
	OpADCIB,//A=A+C+[I+B]
	OpADCVB,//A=A+C+B
	//减法
	OpSUBB,//A=A-[B]
	OpSUBIB,//A=A-[I+B]
	OpSUBVB,//A=A-B
	OpSBCB,//A=A-C-[B]
	OpSBCIB,//A=A-C-[I+B]
	OpSBCVB,//A=A-C-B
	//比较
	OpCMPB,//A与[B]内容进行比较，影响标志位
	OpCMPIB,//A与[B+I]内容进行比较，影响标志位
	OpCMPVB,//A与B比较，影响标志位
	//与
	OpANDB,//A与[B]的内容位与，影响标志位
	OpANDVB,//A与B位与，影响标志位
	OpANDIB,//A与[I+B]位与，影响标志位
	//或
	OpORB,//A与[B]的内容位或，影响标志位
	OpORVB,//A与B位或，影响标志位
	OpORIB,//A与[I+B]位或，影响标志位
	//跳转
	OpJMPB,//跳转到B地址
	OpJZB,//如果Z标志为1，跳转到B单元
	OpJNZB,//如果Z标志为0，跳转到B单元
	OpJSB,//如果S标志为1，跳转到B单元
	OpJNSB,//如果S标志为0，跳转到B单元
	OpJC,//如果C标志为1，跳转到B单元
	OpJNC,//如果C标志为0，跳转到B单元
	//错误指令
	OpError,
};
//指令助记符
static string OpMemonic[52] =
{
	"HALT",	//CPU暂停指令 格式：HALT
	"CLEARAX",		//累加器清0
	"ClEARC",	//进位标志器清0
	"CLEARI",//变址寄存器清0
	"INAXD",	//将10进制数写入累加器
	"INAXB",	//将2进制数写入累加器
	"INAXA",	//将ascii字符写入累加器
	"OUTAXD",	//将累加器数据以10进制形式输出
	"OUTAXB",	//将累加器数据以2进制形式输出
	"OUTAXA",	//将累加器数据以ascii字符形式输出
	"INCAX",//累加器加1，影响标志器
	"DECAX",//累加器减1，影响标志器
	"INCI",//变址寄存器加1，影响标志器
	"DECI",//变址寄存器减1，影响标志器
	"AXTOI",//累加器内容送入变址寄存器 x
	"PUSH",//压栈，堆栈指针减1，累加器的内容压入栈顶。
	"POP",//出栈，堆栈指针加1，将栈顶内容压入栈内
	"LOADBAX",//格式 LDA B ，将B地址单元中的内容送入累加器中，以当前PC所指内存的数值作为地址偏移
	"LOADIBAX",//将变址寄存器+立即数B所指的内存单元的内容送入累加器 A=[I+B]
	"LOADVBAX",//将立即数B送入累加器
	"LOADVBSP",//将立即数B中的内容送到SP寄存器
	"STOREAXB",//[B]=A
	"SIOREAXBI",//[B+I]=A
	//加法
	"ADDB",//A=A+[B]
	"ADDIB",//A=A+[I+B]
	"ADDVB",//A=A+B
	"ADCB",//A=A+C+[B]
	"ADCIB",//A=A+C+[I+B]
	"ADCVB",//A=A+C+B
	//减法
	"SUBB",//A=A-[B]
	"SUBIB",//A=A-[I+B]
	"SUBVB",//A=A-B
	"SBCB",//A=A-C-[B]
	"SBCIB",//A=A-C-[I+B]
	"SBCVB",//A=A-C-B
	//比较
	"CMPB",//A与[B]内容进行比较，影响标志位
	"CMPIB",//A与[B+I]内容进行比较，影响标志位
	"CMPVP",//A与B比较，影响标志位
	//与
	"ANDB",//A与[B]的内容位与，影响标志位
	"ANDVB",//A与B位与，影响标志位
	"ANDIB",//A与[I+B]位与，影响标志位
	//或
	"ORB",//A与[B]的内容位或，影响标志位
	"ORVB",//A与B位或，影响标志位
	"ORIB",//A与[I+B]位或，影响标志位
	//跳转
	"JMPB",//跳转到B地址
	"JZB",//如果Z标志为1，跳转到B单元
	"JNZB",//如果Z标志为0，跳转到B单元
	"JSB",//如果S标志为1，跳转到B单元
	"JNSB",//如果S标志为0，跳转到B单元
	"JC",//如果C标志为1，跳转到B单元
	"JNC",//如果C标志为0，跳转到B单元
	//错误指令
	"OpError",
};