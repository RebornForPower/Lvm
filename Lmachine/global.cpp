//
//  global.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/25.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include "global.h"
#include <vector>
#include <string>
using namespace std;

vector<string> codestream;
vector<MemoryNode> Memory;
byte memory[memsize];
byte data[memsize]; //data segment 
int Mempointer=0;
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
    "OpHALT",
    "OpCLEAR",
    "OpADDB",
    "OpLOADVB",
    "OpSTOREB",
    "OpINCR",
    "OpCMPVB",
    "OpJG",
    "OpJNG",
    "OpERROR"
};

