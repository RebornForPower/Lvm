#include "Assembler.h"
#include "Lmachine.h"
#include "boost/regex.hpp"
using namespace std;
/*
--------------------------------------------------------------
|						汇编器                                |
--------------------------------------------------------------
*/
Assembler::Assembler()
{
	Lmachine * lmachine = new Lmachine;
}
//
void Assembler::Init(string codefilename, Lmachine *& Reflmachine)
{
	TokenIndex = 0;//
	ReadLine();//
	CodeName = codefilename;//
	lmachine = Reflmachine;
}
//
void Assembler::Run_Assembler()
{
	int labelindex, number;
	Bytes lc = 0;
	Bytes Op;
	string Strtoken;
	TokenType type;
	BuildSymbolTable();
	
	for (size_t i = 0; i < LmachineToken.size(); i++)
	{
		type = Lexer(LmachineToken[i], Strtoken);
		switch (type)
		{
		case ASMCode://����ָ��
			Op = lmachine->Opcode(Strtoken); 
			if (Op == OpError) 
			{
				cout << "error mnemonic " << Strtoken << endl;
			}
			lmachine->Memory[lc] = Op; 
			lc = (lc + 1) % MemSize;
			break;
		case ReferLabel://�Ե�ַ���ŵ�����
			Strtoken += ":";
			labelindex = SearchSymbol(Strtoken, 1); 
			if (labelindex == -1)
			{
				cout << "Error: no such a lable" << Strtoken << endl;
			}
			else
			{
				lmachine->Memory[lc] = SymbolTable[labelindex].SymbolAddr;
				lc = (lc + 1) % MemSize;
			}
		case Number:
			number = LmachineToken[i].GetNumber();
			if (number > 0)
				lmachine->Memory[lc] = number % 256;
			else
				lmachine->Memory[lc] = (256 - abs(number) % 256) % 256;
			lc = (lc + 1) % 256;

		default:
			break;
		}

	}
}

TokenType Assembler::Lexer(Token token, string &Strtoken)
{
	TokenType type;
	Bytes command;
	if (isalpha(token.GetID()[0])) 
	{
		command = SearchCmd(token);
		if (command == MaxInstuction&&LmachineToken[TokenIndex + 1].GetID() == ":")
		{
			type = Lablel;
			Strtoken = token.GetID() + LmachineToken[TokenIndex + 1].GetID();
		}
		else if (command == MaxInstuction&&LmachineToken[TokenIndex + 1].GetID() != ":")
		{
			type = ReferLabel;
			Strtoken = token.GetID();
		}
		else
			type = ASMCode;

	}
	else if (isdigit(token.GetID()[0]))
	{
		if (token.IsID)
			type = Number;
	}
	else
		type = UnKnown;
	return type;
}

void Assembler::ReadLine()
{
	string Line;
	ifstream Code(CodeName);
	while (getline(Code, Line)) 
	{
		if (boost::regex_search(Line, what, Regex))
		{
			while (what[0].length() != 0)
			{
				if (what[2].matched == true) //number
				{
					string tokentext(what[2].first, what[2].second);
					int tokennumber = atoi(tokentext.c_str());
					Token token(tokennumber);
					LmachineToken.push_back(token);
					if ((Line.length() - tokentext.length() - 1) == 0)
						break;
					Line = Line.substr((Line.length() - tokentext.length() - 1));
				}
				else if (what[3].matched == true) //ID
				{
					string tokentext(what[3].first, what[3].second);
					Token token(tokentext);
					LmachineToken.push_back(token);
					if ((Line.length() - tokentext.length() - 1) == 0)
						break;
					Line = Line.substr((Line.length() - tokentext.length() - 1));
				}
				if (boost::regex_search(Line, what, Regex))
				{
					continue;
				}
			}
		}
	}
}

int Assembler::SearchSymbol(string symbolname, int sign)
{
	size_t i;
	for (i = 0; i < SymbolTable.size(); i++)
	{
		if (symbolname == SymbolTable[i].SymbolName) 
			break;
	}
	if (i < SymbolTable.size() && sign == 0)
	{
		cout << "the label" << symbolname << "is already defined" << endl;
		return -2;
	}
	else if (i < SymbolTable.size() && sign == 1)
		return i;
	else
		return -1;
}

void Assembler::BuildSymbolTable()
{
	int labelindex;
	TokenType type;
	string Strtoken;
	for (TokenIndex = 0; TokenIndex < LmachineToken.size(); TokenIndex++)
	{
		type = Lexer(LmachineToken[TokenIndex], Strtoken);
		switch (type)
		{
		case Lablel:	
			if (SearchSymbol(LmachineToken[TokenIndex].GetID(), 0) == -1)
			{
				Symbol symbol;
				symbol.SymbolName = Strtoken;
				symbol.SymbolAddr = type - SymbolTable.size();
				symbol.First = NULL;
			}
			break;
		case ReferLabel://���ŵ�ַ�����ã����Ѵ��ڣ�����
			Strtoken += ":";
			labelindex = SearchSymbol(Strtoken, 1);
			if (labelindex == -1) 
				cout << "the label" << Strtoken << "is not defined" << endl;
			else
			{
				SymbolReferenceNode *newnode = new SymbolReferenceNode;
				newnode->ReferenceAddr = type - 1;
				newnode->Next = NULL;
				if (SymbolTable[labelindex].First = NULL)
					SymbolTable[labelindex].First = newnode;
				else
				{
					SymbolReferenceNode * refer = SymbolTable[labelindex].First;
					SymbolReferenceNode * refernode = refer;
					while (refer != NULL)
					{
						refernode = refer;
						refer = refer->Next;
					}
					refernode->Next = newnode;
				}
			}
			break;
		case UnKnown:	
			cout << "the label" << Strtoken << "is Unknown" << endl;
			break;
		default:
			break;
		}
	}
}

Bytes Assembler::SearchCmd(Token token)
{
	int i = 0;
	while (i < MaxInstuction && (lmachine->GetMemonic(i) == token.GetID()))
		i++;
	return (Bytes)i;
}