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
    while (pointer->next!=NULL) {
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
    while (pointer->next!=NULL) {
        index+=pointer->value;
        pointer=pointer->next;
    }
    int idx=string2int(index);
    return idx;
}

int Lmachine::getint(MemoryNode mem)
{
    string num="";
    MemoryNode *pointer=mem.next;
    while (pointer->next!=NULL) {
        num+=pointer->value;
        pointer=pointer->next;
    }
    int number=string2int(num);
    return number;
}

void Lmachine::regoperand(int regindex, regop op,int num)
{
    switch (regindex) {
        case al:
            switch (op) {
                case clear:
                    lvmcpu.al=0;
                    break;
                case assign:
                    num=lvmcpu.al;
                    break;
                case process:
                    lvmcpu.al=num;
                    break;
                case add:
                    lvmcpu.al=lvmcpu.al+num;
                    break;
                default:
                    break;
            }
            break;
            
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
    cout<<" input file path and name:";
    cin>>infile;;
    ofstream searchinfile;
    searchinfile.open(string2char(Lmachine::infile));
    if(!searchinfile)
        cout<<" file "<<infile<<" not find "<<endl;
    while (!searchinfile) {
        cin>>infile;
        searchinfile.open(string2char(infile));
    }
    cout<<" output file path and name:";
    cin>>outfile;
    ofstream newfilepath;
    newfilepath.open(string2char(outfile),ios::out);
    if(newfilepath)
    {
        cout<<" file "<<Lmachine::outfile<<" is create success"<<endl;
    }
    return true;
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
        length=line.length();
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

void Lmachine::initreg()
{
    lvmcpu.al=0;
    lvmcpu.bl=0;
    lvmcpu.cl=0;
    lvmcpu.dl=0;
    lvmcpu.bp=0;
    lvmcpu.ip=0;
    lvmcpu.sp=0;
    lvmcpu.pc=0;
    lvmcpu.bp=0;
}
void Lmachine::lvmrun()
{
    initreg();// init register
    lvmstatus=running;
    do {
        MemoryNode command=Memory[lvmcpu.pc];
        if (command.value=='o') {
            int index=getcmdindex(command);
            switch (index) {
                case OpHALT:
                {
                    lvmstatus=finished;
                    break;
                }
                case OpCLEAR:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    if (reg.value=='r') {
                        int regindex=getregindex(reg);
                        regoperand(regindex, clear, 0);
                        }
                    break;
                }
                case OpSTOREB:
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
                        data[address]=strnum[index];
                        address++;
                    }
                    break;
                }
                case OpLOADVB:
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
                case OpADDB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    int addrvalue=data[num]-'0';
                    regoperand(regindex, add, addrvalue);
                }
                case OpINCR:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    regoperand(regindex, add, 1);
                }
                case OpCMPVB:
                {
                    
                }
                default:
                    break;
            }
        }
    } while (lvmstatus==running);
    
}