//
//  lmachine.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include "lmachine.h"
using namespace std;

#define file "sum.txt"

Lmachine::Lmachine()
{
    
}

int Lmachine::getcmdindex(MemoryNode cmd)
{
    string index="";
    MemoryNode *pointer=cmd.next;
    while (pointer!=NULL) {
        index+=pointer->value;
        pointer=pointer->next;
    }
    int idx=string2int(index);
    return idx;
}

int Lmachine::getregindex(MemoryNode reg)
{
    string index="";
    MemoryNode *pointer=reg.next;
    while (pointer!=NULL) {
        index+=pointer->value;
        pointer=pointer->next;
    }
    int idx=string2int(index)-1; //枚举变量从0开始
    return idx;
}

int Lmachine::getint(MemoryNode mem)
{
    string num="";
    MemoryNode *pointer=&mem;
    while (pointer!=NULL) {
        num+=pointer->value;
        pointer=pointer->next;
    }
    int number=string2int(num);
    return number;
}

void Lmachine::regoperand(int regindex, regop op,int &num)
{
    switch (regindex) {
        case al:
        {
            switch (op) {
                case clear:
                    lvmcpu.al=0+'0';
                    break;
                case assign:
                    num=lvmcpu.al-'0';
                    break;
                case process:
                    lvmcpu.al=num+'0';
                    break;
                case add:
                    lvmcpu.al=((lvmcpu.al-'0')+num)+'0';
                    break;
                case sub:
                    lvmcpu.al=((lvmcpu.al-'0')-num)+'0';
                    break;
                case cmp:
                    if(lvmcpu.al-'0'<num)
                    {
                        lvmcpu.sign=1+'0';
                        lvmcpu.of=0+'0';
                    }
                    else
                    {
                        lvmcpu.sign=0+'0';
                        lvmcpu.of=0+'0';
                    }
                    break;
                default:
                    break;
            }
            break;
        }
        case cl:
        {
            switch (op) {
                case clear:
                    lvmcpu.cl=0+'0';
                    break;
                case add:
                    lvmcpu.cl=((lvmcpu.cl-'0')+num)+'0';
                    break;
                case sub:
                    lvmcpu.cl=((lvmcpu.cl-'0')-num)+'0';
                    break;
                case assign:
                    num=lvmcpu.cl-'0';
                    break;
                case process:
                    lvmcpu.cl=num+'0';
                    break;
                case cmp:
                    if(lvmcpu.cl-'0'<num)
                    {
                        lvmcpu.sign=1+'0';
                        lvmcpu.of=0+'0';
                    }
                    else
                    {
                        lvmcpu.sign=0+'0';
                        lvmcpu.of=0+'0';
                    }
                    break;
                default:
                    break;
            }
        }
        default:
            break;
    }
}
//init static variable
string Lmachine::infile="";
string Lmachine::outfile="";

int Lmachine::string2int(string str)
{
    int num=atoi(str.c_str());
    return num;
}

string Lmachine::int2string(int num)
{
    stringstream s;
    string str;
    s<<num;
    s>>str;
    return str;
}
bool Lmachine::init()
{
    cout<<"input file path and name:";
    cin>>infile;;
    ofstream searchinfile;
    searchinfile.open(string2char(Lmachine::infile));
    if(!searchinfile)
        cout<<"file "<<infile<<" not find "<<endl;
    while (!searchinfile) {
        cin>>infile;
        searchinfile.open(string2char(infile));
    }
    cout<<"output file path and name:";
    cin>>outfile;
    if(outfile=="NULL")
    {
        return true;
    }
    else
    {
        ofstream newfilepath;
        newfilepath.open(string2char(outfile),ios::out);
        if(newfilepath)
        {
            cout<<"file "<<Lmachine::outfile<<" is create success"<<endl;
        }
        return true;
    }
}

char * Lmachine::string2char(string str)
{
    return const_cast<char *>(str.c_str());
}

void Lmachine::readline()
{
    int index,length;
    ifstream code("/Users/Leviathan/Code/Lmachine/Lmachine/sum.txt");
    string line;
    while(getline(code,line))
    {
        length=int(line.length());
        index=0;
        while (index<length) {
            //number
            if (line[index]>='0'&&line[index]<='9') {
                string token="";
                token+=line[index];
                index++;
                while (line[index]>='0'&&line[index]<'9')
                {
                    token+=line[index];
                    index++;
                }
                codestream.push_back(token);
            }
            //id
            else if((line[index]>='a'&&line[index]<'z')||(line[index]>='A'&&line[index]<='Z'))
                {
                    string token="";
                    token+=line[index];
                    index++;
                    while ((line[index]>='a'&&line[index]<'z')||(line[index]>='A'&&line[index]<='Z')||(line[index]>='0'&&line[index]<'9')) {
                        token+=line[index];
                        index++;
                    }
                    codestream.push_back(token);
                }
            //comments
            else if (line[index]=='#')
            {
                index++;
                while (index<length) {
                    index++;
                }
            }
            // " : " sign
            else if(line[index]==':')
            {
                string token="";
                token=line[index];
                codestream.push_back(token);
                index++;
            }
            //space
            else
                index++;
        }
    }
}

void Lmachine::initdata()
{
    for (int index=0; index<memsize; index++) {
        data[index]=0+'0';
    }
}
void Lmachine::initreg()
{
    lvmcpu.al=0;
    lvmcpu.bl=0;
    lvmcpu.cl=0;
    lvmcpu.dl=0;
    lvmcpu.bp=0;
    lvmcpu.ip=0;
    lvmcpu.sp=0;
    lvmcpu.pc=-1;
    lvmcpu.carry=0;
    lvmcpu.bp=0;
}
void Lmachine::lvmrun(Assembler & assembler)
{
    initreg();// init register
    initdata();
    lvmstatus=running;
    cout<<"Lmachine  is running successfully ..."<<endl;
    do {
        lvmcpu.pc++;
        MemoryNode command=Memory[lvmcpu.pc];
        if (command.value=='o') {
            int index=getcmdindex(command);
            switch (index) {
                case OPHALT:
                {
                    lvmstatus=finished;
                    break;
                }
                case OPCLEAR:
                {
                    lvmcpu.pc++;
                    int num=0;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    if (reg.value=='r') {
                        int regindex=getregindex(reg);
                        regoperand(regindex, clear,num);
                        }
                    break;
                }
                case OPSTOREB:
                {
                    lvmcpu.pc++;
                    MemoryNode addr=Memory[lvmcpu.pc];
                    int address=getint(addr);
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int num;
                    int regindex=getregindex(reg);
                    regoperand(regindex, assign,num);
                    string strnum=int2string(num);
                    for(int index=0;index<strnum.length();index++)
                    {
                        char charnum=char(strnum[index]);
                        data[address]=charnum;
                        address++;
                    }
                    break;
                }
                case OPLOAD:
                {
                    lvmcpu.pc++;
                    MemoryNode regget=Memory[lvmcpu.pc];
                    int reggetindex=getregindex(regget);
                    lvmcpu.pc++;
                    MemoryNode regout=Memory[lvmcpu.pc];
                    int regoutindex=getregindex(regout);
                    int pass;
                    regoperand(regoutindex, assign, pass);
                    regoperand(reggetindex, process, pass);
                    break;
                }
                case OPLOADVB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    regoperand(regindex, process, num);
                    break;
                }
                case OPADDB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    int addrvalue=data[num]-'0';
                    regoperand(regindex, add, addrvalue);
                    break;
                }
                case OPSUBVB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    regoperand(regindex, sub,num);
                    break;
                }
                case OPINC:
                {
                    lvmcpu.pc++;
                    int num=1;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    regoperand(regindex, add, num);
                    break;
                }
                case OPCMPVB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    regoperand(regindex, cmp, num);
                    break;
                }
                case OPJG:
                {
                    if(lvmcpu.sign==0+'0'&&lvmcpu.of==0+'0')
                    {
                        lvmcpu.pc++;
                        MemoryNode addr=Memory[lvmcpu.pc];
                        int addrvalue=getint(addr)-1;
                        lvmcpu.pc=addrvalue;
                    }
                    break;
                }
                case OPJNG:
                {
                    if (lvmcpu.sign==1+'0'&&lvmcpu.of==0+'0')
                    {
                        lvmcpu.pc++;
                        MemoryNode addr=Memory[lvmcpu.pc];
                        int addrvalue=getint(addr)-1;
                        lvmcpu.pc=addrvalue;
                    }
                    break;
                }
                case OPPRINTR:
                {
                    lvmcpu.pc++;
                    int num;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    regoperand(regindex, assign, num);
                    cout<<num<<endl;
                    break;
                }
                default:
                    break;
            }
        }
    } while (lvmstatus==running);
}