//
//  assembler.h
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#pragma once
#ifndef LVM_ASSEMBLER_H_
#define LVM_ASSEMBLER_H_

#include <iostream>
#include "lvm_global.h"
using namespace std;


class Assembler
{
public:
    Assembler();
    int searchsymbol(string symbolname,int sign);
    int count_addrlabel(int index);
    void assemblerrun();
    tokentype lexer(string &token,int index);
    void buildsymbol();             //build symbol table
    string int2string(int num);
    bool judge_number(string token);
    int searchcmd(string token);
    int searchreg(string token);
    int getopcode(string token);
};
#endif /* defined(LVM_ASSEMBLER_H_) */
