#include "Assembler.h"
#include "Lmachine.h"
#include "boost/regex.hpp"
using namespace std;
/*
--------------------------------------------------------------
|						汇编器                               |
--------------------------------------------------------------
*/
Assembler::Assembler()
{
	Lmachine * lmachine = new Lmachine;
}
//汇编器初始化
void Assembler::Init(string codefilename, Lmachine *& Reflmachine)
{
	TokenIndex = 0;//将Token记号初始化为0
	ReadLine();//将FILE类型Code名字读取到LmachineToken中
	CodeName = codefilename;//获取用户输入的代码名字
	lmachine = Reflmachine;
}
//运行汇编器
void Assembler::Run_Assembler()
{
	int labelindex, number;
	Bytes lc = 0;//地址计数器
	Bytes Op;
	string Strtoken;
	TokenType type;
	BuildSymbolTable();//第一遍扫描 构建符号表
	/*
	第2遍扫描，将根据符号表，将源程序写入Memory中
	*/
	for (size_t i = 0; i < LmachineToken.size(); i++)
	{
		type = Lexer(LmachineToken[i], Strtoken);
		switch (type)
		{
		case ASMCode://汇编指令
			Op = lmachine->Opcode(Strtoken); //查询汇编指令代表的机器指令
			if (Op == OpError) //错误指令，或不存在的指令
			{
				cout << "error mnemonic " << Strtoken << endl;
			}
			lmachine->Memory[lc] = Op; //存储指令到虚拟机的内存中
			lc = (lc + 1) % MemSize;//地址计器加1
			break;
		case ReferLabel://对地址标号的引用
			Strtoken += ":";
			labelindex = SearchSymbol(Strtoken, 1); //在符号表搜寻，且获取标号的下标
			if (labelindex == -1)//不存在
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
//汇编代码字符流分析
TokenType Assembler::Lexer(Token token, string &Strtoken)
{
	TokenType type;
	Bytes command;
	if (isalpha(token.GetID()[0])) //是地址标号或汇编指令
	{
		command = SearchCmd(token);
		if (command == MaxInstuction&&LmachineToken[TokenIndex + 1].GetID() == ":")
		{
			type = Lablel;//确定为地址标号的定义
			Strtoken = token.GetID() + LmachineToken[TokenIndex + 1].GetID();
		}
		else if (command == MaxInstuction&&LmachineToken[TokenIndex + 1].GetID() != ":")
		{
			type = ReferLabel;//确定对地址标号的引用
			Strtoken = token.GetID();
		}
		else
			type = ASMCode;//确定为汇编指令

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
//将FILE类型Code名字读取到LmachineToken中
void Assembler::ReadLine()
{
	string Line;
	ifstream Code(CodeName);
	while (getline(Code, Line)) //每行读取汇编代码
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
//在符号表中查找符号,sign=0,判断是否进行了重复定义，sign=1,是否已经有该符号，进行更新
int Assembler::SearchSymbol(string symbolname, int sign)
{
	size_t i;
	for (i = 0; i < SymbolTable.size(); i++)
	{
		if (symbolname == SymbolTable[i].SymbolName) //在符号表中找到该符号
			break;
	}
	if (i < SymbolTable.size() && sign == 0)
	{
		cout << "the label" << symbolname << "is already defined" << endl;
		return -2;//标号重复定义
	}
	else if (i < SymbolTable.size() && sign == 1)
		return i;//返回标号在符号表中的下标，用于更新
	else
		return -1;//符号不存在
}
//构造符号表
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
		case Lablel:	//新定义标号，加入符号表
			if (SearchSymbol(LmachineToken[TokenIndex].GetID(), 0) == -1)//符号不存在
			{
				Symbol symbol;
				symbol.SymbolName = Strtoken;
				symbol.SymbolAddr = type - SymbolTable.size();
				symbol.First = NULL;
			}
			break;
		case ReferLabel://标号地址的引用，即已存在，更新
			Strtoken += ":";
			labelindex = SearchSymbol(Strtoken, 1);
			if (labelindex == -1) //符号表不存在
				cout << "the label" << Strtoken << "is not defined" << endl;//提示引用了，但是并未定义
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
		case UnKnown:	//不可识别的符号
			cout << "the label" << Strtoken << "is Unknown" << endl;
			break;
		default:
			break;
		}
	}
}
//查询汇编指令表，返回对应的机器指令，机器指令隐含为指令数组的下标
Bytes Assembler::SearchCmd(Token token)
{
	int i = 0;
	while (i < MaxInstuction && (lmachine->GetMemonic(i) == token.GetID()))
		i++;
	return (Bytes)i;
}