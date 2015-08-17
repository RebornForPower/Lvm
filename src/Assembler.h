#pragma once
#include "Token.h"
#include "Global.h"
using namespace std;
class Lmachine;
//汇编器
class Assembler
{
public:
	Lmachine * lmachine;
	string CodeName;
	size_t TokenIndex;
	vector<Token> LmachineToken;
	vector<Symbol> SymbolTable;
	Assembler();
	~Assembler();
	void Init(string codefilename, Lmachine * &lmachine);
	TokenType Lexer(Token token, string &Strtoken);
	void ReadLine();
	void Run_Assembler();	
	void BuildSymbolTable();
	int  SearchSymbol(string symbolname, int sign);
        Bytes SearchCmd(Token token);
};
