#pragma once
#include "Token.h"
#include "Global.h"
using namespace std;
class Lmachine;
//汇编器
class Assembler
{
public:
	/*
	数据成员
	*/
	Lmachine * lmachine;
	string CodeName;//代码文件名字
	size_t TokenIndex;//token记号索引
	vector<Token> LmachineToken; //汇编代码字符流
	vector<Symbol> SymbolTable;//符号表动态数组
	/*
	成员函数
	*/
	Assembler();
	~Assembler();
	void Init(string codefilename, Lmachine * &lmachine);//初始化
	TokenType Lexer(Token token, string &Strtoken);//汇编代码字符流分析
	void ReadLine();//将FILE类型Code名字读取到LmachineToken中
	void Run_Assembler();	//运行汇编器
	void BuildSymbolTable();//构建符号表
	int  SearchSymbol(string symbolname, int sign);//在符号表中查找符号
	Bytes SearchCmd(Token token);//查询汇编指令表，返回对应的机器指令，机器指令隐含为指令数组的下标
};