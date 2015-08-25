//
//  global.h
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
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
#define opnum 9
#define regnum 12

extern byte memory[memsize];//vm memory
extern vector<string> codestream;
extern string strop[];
extern string stringregister[];
//reference symbol
struct refsymbol
{
    int refsymboladdr;
    refsymbol *next;
};
//sylbol
struct symbol
{
    string symbolname;
    int symboladdr; //symbol address
    refsymbol * first;
};

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

enum tokentype
{
    op,
    reg,
    label,
    reflabel,
    number,
    unknow
};
enum op
{
    /* 
        B ->[B]即B地址单元中的内容
        VB->立即数本身
    */
    OpHALT,
    OpCLEAR,    //clear register
    OpADDB,
    OpLOADVB,
    OpSTOREB, //[B]=register
    OpINC,     //register=register+1
    OpCMPVB,    //compare VB
    OpJG,
    OpJNG,
    OpERROR
};

#endif /* defined(__Lmachine__global__) */
