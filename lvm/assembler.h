//
//  assembler.h
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#pragma once
#ifndef __Lmachine__assembler__
#define __Lmachine__assembler__

#include <iostream>
#include "global.h"
using namespace std;


class Assembler
{
public:
    Assembler();
    int searchsymbol(string symbolname,int sign);
    void assemblerrun();
    tokentype lexer(string &token,int index);
    void buildsymbol();             //build symbol table
    string int2string(int num);
    int searchcmd(string token);
    int searchreg(string token);
    int getopcode(string token);
};
#endif /* defined(__Lmachine__assembler__) */
