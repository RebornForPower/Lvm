//
//  lmachine.h
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#pragma once
#ifndef __Lvm__lmachine__
#define __Lvm__lmachine__

#include <iostream>
#include <vector>
#include <string>
#include "global.h"

using namespace std;


//virtual machine
class Lmachine
{
public:
    //funciton
    Lmachine();
    bool init();
    void lvmrun();
    void readline();
    char * string2char(string str);
    //data
    static string infile;
    static string outfile;
    
};
#endif /* defined(__Lvm__lmachine__) */
