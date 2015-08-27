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

typedef char byte;//byte
#define memsize 1024 //1024 byte
#define keynum 21

extern vector<string> codestream;
extern string strkey[];
extern int Mempointer; //memsize max
//Memory Node
struct MemoryNode
{
    byte value;
    MemoryNode *next;
};

extern vector<MemoryNode> Memory;

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
    int ir;
    byte sp;
    int pc;
    byte bp;
    //flag register
    byte carry;
    byte zero;
    byte sign;
};
enum regop
{
    add,
    sub,
    assign,
    clear
};
//virtual machine running status
enum status
{
    running,
    finished
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
enum key
{
    //register
    al,
    bl,
    cl,
    dl,
    ip,
    ir,
    sp,
    pc,
    bp,
    carry,
    zero,
    sign,
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
