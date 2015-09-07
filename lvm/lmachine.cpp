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
#include <algorithm>
#include "lmachine.h"
using namespace std;

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

string Lmachine::getstring(MemoryNode mem)
{
    string str="";
    MemoryNode *pointer=mem.next;
    while (pointer!=NULL) {
        str+=pointer->value;
        pointer=pointer->next;
    }
    return str;
}

string Lmachine::getdatavalue(int addr)
{
    string strvalue;
    char value=data[addr];
    if(value=='$')
    {
        strvalue='0';
    }
    else
    {
        strvalue=value;
        addr++;
        while(data[addr]!='$')
            {
                value=data[addr];
                strvalue+=value;
                addr++;
            }
    }
    return strvalue;
}

void Lmachine::cleareg(int regindex)
{
    int num=0;
    regoperand(regindex, clear, num);
}
void Lmachine::regoperand(int regindex, regop op,int &num)
{
    switch (regindex) {
        case al:
        {
            switch (op) {
                case clear:
                    for (int index=0; index<8; index++) {
                        lvmcpu.al[index]=0+'0';
                    }
                    break;
                case assign:
                {
                    string strnum;
                    for (int index=0; index<8; index++) {
                        strnum+=lvmcpu.al[index];
                    }
                    num=string2int(strnum);
                    break;
                }
                case process:
                {
                    cleareg(regindex);
                    string strnum;
                    size_t index=0;
                    int strindex;
                    strnum=int2string(num);
                    for (index=8-strnum.length(),strindex=0; index<8; strindex++,index++) {
                        lvmcpu.al[index]=strnum[strindex];
                    }
                    break;
                }
                case add:
                {
                    string regnum;
                    size_t index;
                    int strindex;
                    for (int index=0; index<8; index++) {
                        regnum+=lvmcpu.al[index];
                    }
                    int regnumber=string2int(regnum);
                    int add=regnumber+num;
                    string addnum=int2string(add);
                    for (index=8-addnum.length(),strindex=0; index<8; strindex++,index++) {
                        lvmcpu.al[index]=addnum[strindex];
                    }
                    break;
                }
                case sub:
                {
                    string regnum;
                    size_t index;
                    int strindex;
                    for (int index=0; index<8; index++) {
                        regnum+=lvmcpu.al[index];
                    }
                    int subnum=string2int(regnum)-num;
                    string strsubnum=int2string(subnum);
                    for (index=8-strsubnum.length(),strindex=0; index<8; strindex++,index++) {
                        lvmcpu.al[index]=strsubnum[strindex];
                    }
                    break;
                }
                case cmp:
                {
                    string strregnum;
                    for (int index=0;index<8;index++) {
                        strregnum+=lvmcpu.al[index];
                    }
                    int regnum=string2int(strregnum);
                    if(regnum<num)
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
                }
                default:
                    break;
            }
            break;
        }
        case cl:
        {
            switch (op) {
                case clear:
                    for (int index=0; index<8; index++) {
                        lvmcpu.cl[index]=0+'0';
                    }
                    break;
                case add:
                {
                    string regnum;
                    size_t index;
                    int strindex;
                    for (int index=0; index<8; index++) {
                        regnum+=lvmcpu.cl[index];
                    }
                    int regnumber=string2int(regnum);
                    int add=regnumber+num;
                    string addnum=int2string(add);
                    for (index=8-addnum.length(),strindex=0; index<8; strindex++,index++) {
                        lvmcpu.cl[index]=addnum[strindex];
                    }
                    break;
                }
                case sub:
                {
                    string regnum;
                    size_t index;
                    int strindex;
                    for (int index=0; index<8; index++) {
                        regnum+=lvmcpu.cl[index];
                    }
                    int subnum=string2int(regnum)-num;
                    string strsubnum=int2string(subnum);
                    for (index=8-strsubnum.length(),strindex=0; index<8; strindex++,index++) {
                        lvmcpu.cl[index]=strsubnum[strindex];
                    }
                    break;
                }
                case assign:
                {
                    string strnum;
                    for (int index=0; index<8; index++) {
                        strnum+=lvmcpu.cl[index];
                    }
                    num=string2int(strnum);
                    break;
                }
                case process:
                {
                    string strnum;
                    size_t index;
                    int strindex;
                    strnum=int2string(num);
                    for (index=8-strnum.length(),strindex=0; index<8; strindex++,index++) {
                        lvmcpu.cl[index]=strnum[strindex];
                    }
                    break;
                }
                case cmp:
                {
                    string strregnum;
                    for (int index=0;index<8;index++) {
                        strregnum+=lvmcpu.cl[index];
                    }
                    int regnum=string2int(strregnum);
                    if(regnum<num)
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
                }
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
    cin>>infile;
    ifstream searchinfile;
    searchinfile.open(string2char(Lmachine::infile)); //readline()
    if(!searchinfile)
        cout<<"file "<<infile<<" not find "<<endl;
    while (!searchinfile) {
        cin>>infile;
        searchinfile.open(string2char(infile));
    }
    cout<<"output file path and name:";
    cin>>outfile;
    if(outfile=="null")
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
    ifstream code;
    code.open(string2char(Lmachine::infile));
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
            //string
            else if(line[index]=='"')
            {
                string token="";
                token='"';
                codestream.push_back(token);
                index++;
                token="";
                while(line[index]!='"')
                {
                    token+=line[index];
                    index++;
                }
                codestream.push_back(token);
                token="";
                token='"';
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
        data[index]='$';
    }
}

void Lmachine::lvmrun(Assembler & assembler)
{
    lvmcpu.pc=-1;
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
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int num;
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode addr=Memory[lvmcpu.pc];
                    int address=getint(addr);
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
                case OPLOADB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    int addrvalue=data[num]-'0';
                    regoperand(regindex, process,addrvalue);
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
                    int addrvalue=string2int(getdatavalue(num));
                    regoperand(regindex, add, addrvalue);
                    break;
                }
                case OPADDVB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    regoperand(regindex,add, num);
                    break;
                }
                case OPSUBB:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    int addrvalue=data[num]-'0';
                    regoperand(regindex,sub,addrvalue);
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
                case OPDEC:
                {
                    lvmcpu.pc++;
                    int num=1;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    regoperand(regindex, sub, num);
                    break;
                }
                case OPLESTR:
                {
                    string str;
                    lvmcpu.pc++;
                    MemoryNode address=Memory[lvmcpu.pc];
                    int addr=getint(address);
                    lvmcpu.pc++;
                    MemoryNode strcontext=Memory[lvmcpu.pc];
                    if (strcontext.value=='s') {
                        str=getstring(strcontext);
                    }
                    for(int index=0;index<str.length();index++)
                    {
                        data[addr]=str[index];
                        addr++;
                    }
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
