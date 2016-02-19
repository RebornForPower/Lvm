//
//  lmachine.h
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#pragma once
#ifndef LVM_LMACHINE_H_
#define LVM_LMACHINE_H_

#include <iostream>
#include <vector>
#include <string>
#include "lvm_assembler.h"
#include "lvm_global.h"

using namespace std;


//virtual machine
class Lmachine
{
public:
    //funciton
    Lmachine();
    bool init();
    void initdata();//init data segment
    void lvmrun(Assembler & assembler);
    void readline();
    char * string2char(string str);
    int string2int(string str);
    string int2string(int num);
    int getregindex(MemoryNode reg);
    int getcmdindex(MemoryNode cmd);
    int getint(MemoryNode mem);
    string getstring(MemoryNode mem);
    string getdatavalue(int addr);
    void regoperand(int regindex,regop op,int & num,string &str);
    void cleareg(int regindex);
    int findend(string variablename);
    //data
    cpu lvmcpu;
    status lvmstatus;
    static string infile;
    static string outfile;
    
};
#endif /* defined(LVM_LMACHINE_H_) */
