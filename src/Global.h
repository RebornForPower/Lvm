#pragma once

#include <string>
#include <boost/regex.hpp>
using namespace std;

static boost::regex Regex("([0-9]+)|([A-Z_a-z]*[A-Z_a-z0-9]+)|(:)|(;.*)"); //正则表达式
static boost::smatch what;
typedef unsigned char Bytes; //一个字节
#define MemSize 256 //虚拟机内存
#define MaxInstuction 51 //汇编指令数目
//同名引用节点
struct SymbolReferenceNode
{
	Bytes ReferenceAddr;	   //同名引用的符号的内存地址
	SymbolReferenceNode * Next;//下一个同名引用的节点
};
//符号定义
struct Symbol
{
	string SymbolName;//符号名字
	Bytes SymbolAddr;	//符号内存地址·
	SymbolReferenceNode * First;//首个符号
};
//cpu设计
struct CPU
{
	Bytes Accumulator;
	Bytes StackPointer;
	Bytes IndexRegister;
	Bytes InstructionRegister;
	Bytes ProgramCounter;
	Bytes BasePointer;
	bool Carry;
	bool Zero;
	bool Sign;
};
//虚拟机运行状态
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
	Success,
	Failed,
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
//虚拟机指令表
enum Operand
{
	/*
         * B代表立即数
         * 前面带V表示立即数本身
         * 不加V代表[B],即B地址单元中的内容
	*/
	OpHALT,	//CPU暂停指令
	OpCLEARAX,		//AX清零
	OpClEARC,	//进位标志器清零
	OpCLEARI,//变址寄存器清零
	OpINAXD,	
	OpINAXB,	
	OpINAXA,	
	OpOUTAXD,	
	OpOUTAXB,	
	OpOUTAXA,	
	OpINCAX,
	OpDECAX,
	OpINCI,
	OpDECI,
	OpAXTOI,
	OpPUSH,
	OpPOP,
	OpLOADBAX,
	OpLOADIBAX,
	OpLOADVBAX,
	OpLOADVBSP,
	OpSTOREAXB,
	OpSIOREAXBI,
	OpADDB,//A=A+[B]
	OpADDIB,//A=A+[I+B]
	OpADDVB,//A=A+B
	OpADCB,//A=A+C+[B]
	OpADCIB,//A=A+C+[I+B]
	OpADCVB,//A=A+C+B
	
	OpSUBB,//A=A-[B]
	OpSUBIB,//A=A-[I+B]
	OpSUBVB,//A=A-B
	OpSBCB,//A=A-C-[B]
	OpSBCIB,//A=A-C-[I+B]
	OpSBCVB,//A=A-C-B
	
	OpCMPB,
	OpCMPIB,
	OpCMPVB,
	
	OpANDB,
	OpANDVB,
	OpANDIB,
	
	OpORB,
	OpORVB,
	OpORIB,
	
	OpJMPB,
	OpJZB,
	OpJNZB,
	OpJSB,
	OpJNSB,
	OpJC,
	OpJNC,
	
	OpError,
};
static string OpMemonic[52] =
{
	"HALT",	
	"CLEARAX",
	"ClEARC",
	"CLEARI",
	"INAXD",
	"INAXB",
	"INAXA",
	"OUTAXD",
	"OUTAXB",
	"OUTAXA",
	"INCAX",
	"DECAX",
	"INCI",
	"DECI",
	"AXTOI",
	"PUSH",
	"POP",
	"LOADIBAX",
	"LOADVBAX",
	"LOADVBSP",
	"STOREAXB",
	"SIOREAXBI",
	"ADDB",//A=A+[B]
	"ADDIB",//A=A+[I+B]
	"ADDVB",//A=A+B
	"ADCB",//A=A+C+[B]
	"ADCIB",//A=A+C+[I+B]
	"ADCVB",//A=A+C+B
	"SUBB",//A=A-[B]
	"SUBIB",//A=A-[I+B]
	"SUBVB",//A=A-B
	"SBCB",//A=A-C-[B]
	"SBCIB",//A=A-C-[I+B]
	"SBCVB",//A=A-C-B
	"CMPB",
	"CMPIB",
	"CMPVP",
	"ANDB",
	"ANDVB",
	"ANDIB",
	"ORB",
	"ORVB",
	"ORIB",
	"JMPB",
	"JZB",
	"JNZB",
	"JSB",
	"JNSB",
	"JC",
	"JNC",
	"OpError",
};
