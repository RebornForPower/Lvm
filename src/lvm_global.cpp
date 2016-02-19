//
//  global.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/25.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include "lvm_global.h"
#include <vector>
#include <string>
using namespace std;

vector<string> codestream;
vector<symbol *> symboltable;
vector<MemoryNode> Memory;
byte memory[memsize];
byte data[memsize]; //data segment

int Mempointer=0;
string parastr=" ";
int paraint=0;
string strkey[]=
{
    //register
    "AL",
    "BL",
    "CL",
    "DL",
    "IP",
    "IR",
    "SP",
    "PC",
    "BP",
    "CARRY",
    "ZERO",
    "SIGN",
    //operand
    "OPHALT",
    "OPCLEAR",
    "OPINIT",
    "OPINITLIST",
    "OPASSIGN",
    "OPBINADD",
    "OPBINSUB",
    "OPBINMUL",
    "OPBINDIV",
    "OPADDB",
    "OPADDVB",
    "OPSUBB",
    "OPSUBVB",
    "OPLOAD",
    "OPLOADVB",
    "OPLOADB",
    "OPSTOREB",
    "OPINC",
    "OPDEC",
    "OPCMPVB",
    "OPJG",
    "OPJNG",
    "OPLESTR",
    "OPPRINTR",
    "OPPRINTRLIST",
    "OPEND",
    "OPPAUSE",
    "OPERROR"
};

bool is_symbol(string symbolname)
{
    for(auto symbol:symboltable)
    {
        if(symbol->symbolname==symbolname)
            return true;
    }
    return false;
}

symbol * getsymbol(string symbolname)
{
    symbol *sym=NULL;
    for(int index=0;index<symboltable.size();index++)
    {
        if(symbolname==symboltable[index]->symbolname)
        {
            sym=symboltable[index];
            return sym;
        }
        else
            continue;
    }
    return sym;
}

var_type getsymbol_type(string symbolname)
{
    for (auto symbol:symboltable) {
        if (symbolname==symbol->symbolname) {
            return symbol->type;
        }
    }
    return error_type;
}
