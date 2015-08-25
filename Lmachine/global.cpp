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
byte memory[memsize];
string strop[]=
{
    "OpHALT",
    "OpCLEAR",
    "OpADDB",
    "OpLOADVB",
    "OpSTOREB",
    "OpINC",
    "OpCMPVB",
    "OpJG",
    "OpJNG",
    "OpERROR"
};
string stringregister[]=
{
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
    "SIGN"
};

