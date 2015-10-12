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
#define keynum 37


/*
    Global Variable
*/
extern vector<string> codestream;
extern byte memory[];
extern byte data[];
extern string strkey[];
extern int Mempointer; //memsize max

extern string parastr; //regoperand parameter
extern int paraint;    //regoperand parameter
//Memory Node
struct MemoryNode
{
    byte value;
    MemoryNode *next;
};

extern vector<MemoryNode> Memory;

//token type
enum tokentype
{
    op,
    reg,
    addr_label,
    var_symbol,
    escape_symbol,
    number,
    str,
    quotes,        // "
    unknow
};

//escape_symbol
enum escape
{
    space, //"\s"
    newline//"\n"
};
//vartiable type
enum var_type
{
    addr_symbol,
    int_var,
    int_array,
    str_var
};

//symbol
class symbol
{
public:
    string symbolname;
    int int_value;
    string str_value;
    int label_addr; //addr_label address
    bool define;
    var_type type;
};

extern vector<symbol> symboltable;

//cpu
struct cpu
{
    //register
    char al[8];
    char bl[8];
    char cl[8];
    char dl[128];
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

//register operation
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
    OPINIT,     //id=register
    OPASSIGN,   //id=reg/num
    OPBINADD,   //id1=id2+id3
    OPBINSUB,   //id1=id2-id3
    OPBINMUL,   //id1=id2*id3
    OPBINDIV,   //id1=id2/id3
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
    OPEND,      //end code block
    OPERROR
};

/*
    Global Function
*/
symbol * getsymbol(string symbolname);

#endif /* defined(__Lmachine__global__) */
