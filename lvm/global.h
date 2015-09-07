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
#define keynum 30

extern vector<string> codestream;
extern byte memory[];
extern byte data[];
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
    char al[8];
    char bl[8];
    char cl[8];
    char dl[8];
    char ip[8];
    int ir;
    byte sp;
    byte of;
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
    assign,//num=register
    process,//register=num
    cmp,
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
    str,
    quotes,// "
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
    OPHALT,
    OPCLEAR,    //register=0
    OPADDB,     //register=register+[B]
    OPADDVB,    //register=register+B
    OPSUBB,     //register=register-[B]
    OPSUBVB,    //register=register-B
    OPLOAD,     //register1=register2
    OPLOADVB,   //register=B
    OPLOADB,    //register=[B]
    OPSTOREB,   //[B]=register
    OPINC,      //register=register+1
    OPDEC,      //register=register-1
    OPCMPVB,    //compare register and B
    OPJG,
    OPJNG,
    OPLESTR,    //[B]=string
    OPPRINTR,   //print register value to terminal
    OPERROR
};

#endif /* defined(__Lmachine__global__) */
