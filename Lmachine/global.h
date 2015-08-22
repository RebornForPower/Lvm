//
//  global.h
//  Lmachine
//
//  Created by 孙海清 on 15/8/21.
//  Copyright (c) 2015年 孙海清. All rights reserved.
//

#pragma once
#ifndef __Lmachine__global__
#define __Lmachine__global__

#include <iostream>
#include <string>
#include <vector>
using namespace std;

typedef unsigned char byte;//byte
#define memsize 1024 //1024 byte
vector<string> codestream; //code token stream

//string to char *
char * string2char(string str)
{
    return const_cast<char *>(str.c_str());
}
//cpu
struct cpu
{
    //register
    byte al;
    byte bl;
    byte cl;
    byte dl;
    byte ip;
    byte ir;
    byte sp;
    byte pc;
    byte bp;
    //flag register
    byte carry;
    byte zero;
    byte sign;
};

//virtual machine running status
enum status
{
    running,
    finish,
};

enum lvmerror
{
    operanderror,
    dataerror,
    unknowerror,
};

enum lvmendstatus
{
    success,
    fail,
};

#endif /* defined(__Lmachine__global__) */
