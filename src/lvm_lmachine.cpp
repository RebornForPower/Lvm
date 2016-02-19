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
#include "lvm_lmachine.h"
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
    int number=0;
    if (mem.value=='a') {
        MemoryNode *pointer=mem.next;
        while (pointer->value!='$')
            pointer=pointer->next;
        pointer=pointer->next;
        while (pointer!=NULL) {
            num+=pointer->value;
            pointer=pointer->next;
        }
        if(is_symbol(num))
            number=getsymbol(num)->int_value;
        else
            number=string2int(num);
        return number;
    }
    else
    {
        MemoryNode *pointer=mem.next;
        while (pointer!=NULL) {
            num+=pointer->value;
            pointer=pointer->next;
        }
        number=string2int(num);
        return number;
    }
}

string Lmachine::getstring(MemoryNode mem)
{
    string str="";
    if (mem.value=='a') {
        MemoryNode *pointer=mem.next;
        while (pointer->value!='$'&&pointer!=NULL) {
            str+=pointer->value;
            pointer=pointer->next;
        }
        return str;
    }
    else
    {
        MemoryNode *pointer=mem.next;
        while (pointer!=NULL) {
            str+=pointer->value;
            pointer=pointer->next;
        }
        return str;
    }
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
    regoperand(regindex, clear, paraint,parastr);
}

int Lmachine::findend(string addr_label)
{
    int index=0;
    for (index=0;index<Memory.size(); index++) {
        MemoryNode node=Memory[index];
        if(node.value=='o'&&getcmdindex(node)==37)
        {
            index++;
            MemoryNode operand=Memory[index];
            string stroperand=getstring(operand);
            if (stroperand==addr_label) {
                return index;
            }
        }
    }
    return -1;
}

void Lmachine::regoperand(int regindex, regop op,int &num,string & str)
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
        case dl:
        {
            switch (op)
            {
                case clear:
                {
                    for(int index=0;index<128;index++)
                        lvmcpu.dl[index]=str[0];
                    break;
                }
                case process:
                {
                    cleareg(regindex);
                    for (int strindex=0; strindex<str.length(); strindex++) {
                        lvmcpu.dl[strindex]=str[strindex];
                    }
                    break;
                }
                case assign:
                {
                    int index=0;
                    while (lvmcpu.dl[index]!=' ') {
                        str+=lvmcpu.dl[index];
                        index++;
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
    code.open(infile);
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
                while ((line[index]>='a'&&line[index]<'z')||(line[index]>='A'&&line[index]<='Z')||(line[index]>='0'&&line[index]<='9')) {
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
            //string
            else if(line[index-1]=='"')
            {
                string token="";
                while (line[index]!='"') {
                    token+=line[index];
                    index++;
                }
                codestream.push_back(token);
            }
            //symbol
            else if (line[index]=='"'||line[index]=='\\'||line[index]=='['||line[index]==']')
            {
                string token="";
                token+=line[index];
                index++;
                codestream.push_back(token);
            }
            //address label symbol
            else if(line[index]==':')
            {
                string token="";
                token+=line[index];
                index++;
                codestream.push_back(token);
            }
            //array end symbol
            else if(line[index]=='$')
            {
                string token="";
                token+=line[index];
                index++;
                codestream.push_back(token);
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
                    cout<<endl;
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
                        string str;
                        regoperand(regindex, clear,num,parastr);
                    }
                    break;
                }
                case OPINIT:
                {
                    lvmcpu.pc++;
                    MemoryNode var=Memory[lvmcpu.pc];
                    string var_name=getstring(var);
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    symbol *sym=getsymbol(var_name);
                    if(sym->define==true)
                    {
                        cout<<"the variable "<<var_name<<" is already define !"<<endl;
                        break;
                    }
                    //string
                    if(regindex==3)
                    {
                        string str;
                        regoperand(regindex, assign, paraint, str);
                        sym->str_value=str;
                        sym->type=str_var;
                        sym->define=true;
                    }
                    //int
                    else
                    {
                        int num;
                        regoperand(regindex, assign, num, parastr);
                        sym->int_value=num;
                        sym->type=int_var;
                        sym->define=true;
                    }
                    break;
                }
                case OPINITLIST:
                {
                    lvmcpu.pc++;
                    MemoryNode var=Memory[lvmcpu.pc];
                    string var_name=getstring(var);
                    lvmcpu.pc++;
                    symbol *sym=getsymbol(var_name);
                    if(sym->define==true)
                    {
                        cout<<"the variable "<<var_name<<" is already define !"<<endl;
                        break;
                    }
                    sym->type=int_array;
                    while (Memory[lvmcpu.pc].value!='$') {
                        MemoryNode value=Memory[lvmcpu.pc];
                        int number=getint(value);
                        sym->array_value.push_back(number);
                        lvmcpu.pc++;
                    }
                    break;
                }
                case OPASSIGN:
                {
                    string var_name,assign_name;
                    int var_index=0,assign_index=0;
                    lvmcpu.pc++;
                    MemoryNode variable=Memory[lvmcpu.pc];
                    if (variable.value=='a') {
                        var_name=getstring(variable);
                        var_index=getint(variable);
                    }
                    else
                        var_name=getstring(variable);
                    symbol *var_sym=getsymbol(var_name);
                    lvmcpu.pc++;
                    MemoryNode assign_value=Memory[lvmcpu.pc];
                    if (assign_value.value=='a') {
                        assign_name=getstring(assign_value);
                        assign_index=getint(assign_value);
                    }
                    else
                        assign_name=getstring(assign_value);
                    symbol *assign_sym=getsymbol(assign_name);
                    //register
                    if(assign_value.value=='r')
                    {
                        int regindex=getregindex(assign_value);
                        if(regindex==3) //DL register. string
                        {
                            string str;
                            regoperand(regindex, assign, paraint, str);
                            var_sym->str_value=str;
                            var_sym->type=str_var;
                        }
                        else //number
                        {
                            int num;
                            regoperand(regindex, assign, num, parastr);
                            if(var_sym->type==int_array)
                                var_sym->array_value[index]=num;
                            else
                            {
                                var_sym->int_value=num;
                                var_sym->type=int_var;
                            }
                        }
                    }
                    //value
                    else
                    {
                        //number
                        if(assign_value.value=='n')
                        {
                            int num=getint(assign_value);
                            if (var_sym->type==int_array) {
                                var_sym->array_value[index]=num;
                            }
                            else
                            {
                                var_sym->int_value=num;
                                var_sym->type=int_var;
                            }
                        }
                        //string
                        else if(assign_value.value=='s')
                        {
                            string str=getstring(assign_value);
                            var_sym->str_value=str;
                            var_sym->type=str_var;
                        }
                        //variable
                        else if(assign_value.value=='v')
                        {
                            if(assign_sym->type==int_var)
                            {
                                if (var_sym->type==int_array) {
                                    var_sym->array_value[var_index]=assign_sym->int_value;
                                }
                                else
                                {
                                    var_sym->int_value=assign_sym->int_value;
                                    var_sym->type=int_var;
                                }
                            }
                            else if(assign_sym->type==str_var)
                            {
                                var_sym->str_value=assign_sym->str_value;
                                var_sym->type=str_var;
                            }
                        }
                        //array value
                        else if(assign_value.value=='a')
                        {
                            symbol *strassign=getsymbol(assign_name);
                            if (variable.value=='a') {
                                var_sym->array_value[var_index]=strassign->array_value[assign_index];
                            }
                            else
                            {
                                var_sym->int_value=strassign->array_value[assign_index];
                                var_sym->type=int_var;
                            }
                        }
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
                    regoperand(regindex, assign,num,parastr);
                    string strnum=int2string(num);
                    for(int index=0;index<strnum.length();index++)
                    {
                        char charnum=char(strnum[index]);
                        data[address]=charnum;
                        address++;
                    }
                    break;
                }
                case OPLOAD: //reg=reg
                {
                    lvmcpu.pc++;
                    MemoryNode regget=Memory[lvmcpu.pc];
                    int reggetindex=getregindex(regget);
                    lvmcpu.pc++;
                    MemoryNode outvalue=Memory[lvmcpu.pc];
                    int regoutindex=getregindex(outvalue);
                    int pass;
                    regoperand(regoutindex, assign, pass,parastr);
                    regoperand(reggetindex, process, pass,parastr);
                    break;
                }
                case OPLOADVB: //reg=B
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode outvalue=Memory[lvmcpu.pc];
                    //string DL
                    if (regindex==3&&(outvalue.value=='s'||getsymbol(getstring(outvalue))->type==str_var))
                    {
                        if (outvalue.value=='s')
                        {
                            string value=getstring(outvalue);
                            regoperand(regindex, process, paraint,value);
                        }
                        else if(getsymbol(getstring(outvalue))->type==str_var)
                        {
                            string value=getsymbol(getstring(outvalue))->str_value;
                            regoperand(regindex, process, paraint, value);
                        }
                    }
                    //int
                    else if(regindex!=3)
                    {
                        int num=getint(outvalue);
                        regoperand(regindex, process, num,parastr);
                    }
                    break;
                }
                case OPLOADB: //reg=[B]
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    lvmcpu.pc++;
                    MemoryNode memnum=Memory[lvmcpu.pc];
                    int num=getint(memnum);
                    int addrvalue=data[num]-'0';
                    regoperand(regindex, process,addrvalue,parastr);
                    break;
                }
                case OPBINADD:
                {
                    lvmcpu.pc++;
                    MemoryNode save=Memory[lvmcpu.pc];
                    string strsave=getstring(save);
                    symbol *savesym=getsymbol(strsave);
                    lvmcpu.pc++;
                    MemoryNode add1=Memory[lvmcpu.pc];
                    int add1num;
                    if (add1.value=='v')
                    {
                        string stradd1=getstring(add1);
                        add1num=getsymbol(stradd1)->int_value;
                    }
                    else
                        add1num=getint(add1);
                    lvmcpu.pc++;
                    MemoryNode add2=Memory[lvmcpu.pc];
                    int add2num;
                    if (add2.value=='v') {
                        string stradd2=getstring(add2);
                        add2num=getsymbol(stradd2)->int_value;
                    }
                    else
                        add2num=getint(add2);
                    int savenum=add1num+add2num;
                    savesym->int_value=savenum;
                    savesym->type=int_var;
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
                    regoperand(regindex, add, addrvalue,parastr);
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
                    regoperand(regindex,add, num,parastr);
                    break;
                }
                case OPBINSUB:
                {
                    lvmcpu.pc++;
                    MemoryNode save=Memory[lvmcpu.pc];
                    string strsave=getstring(save);
                    symbol * savesym=getsymbol(strsave);
                    lvmcpu.pc++;
                    MemoryNode sub1=Memory[lvmcpu.pc];
                    int sub1num;
                    if (sub1.value=='v')
                    {
                        string strsub1=getstring(sub1);
                        sub1num=getsymbol(strsub1)->int_value;
                    }
                    else
                        sub1num=getint(sub1);
                    lvmcpu.pc++;
                    MemoryNode sub2=Memory[lvmcpu.pc];
                    int sub2num;
                    if (sub2.value=='v') {
                        string strsub2=getstring(sub2);
                        sub2num=getsymbol(strsub2)->int_value;
                    }
                    else
                        sub2num=getint(sub2);
                    int savenum=sub1num-sub2num;
                    savesym->int_value=savenum;
                    savesym->type=int_var;
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
                    regoperand(regindex,sub,addrvalue,parastr);
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
                    regoperand(regindex, sub,num,parastr);
                    break;
                }
                case OPBINMUL:
                {
                    lvmcpu.pc++;
                    MemoryNode save=Memory[lvmcpu.pc];
                    string strsave=getstring(save);
                    symbol * savesym=getsymbol(strsave);
                    lvmcpu.pc++;
                    MemoryNode mul1=Memory[lvmcpu.pc];
                    int mul1num;
                    if (mul1.value=='v')
                    {
                        string strmul1=getstring(mul1);
                        mul1num=getsymbol(strmul1)->int_value;
                    }
                    else
                        mul1num=getint(mul1);
                    lvmcpu.pc++;
                    MemoryNode mul2=Memory[lvmcpu.pc];
                    int mul2num;
                    if (mul2.value=='v') {
                        string strmul2=getstring(mul2);
                        mul2num=getsymbol(strmul2)->int_value;
                    }
                    else
                        mul2num=getint(mul2);
                    int savenum=mul1num*mul2num;
                    savesym->int_value=savenum;
                    savesym->type=int_var;
                    break;
                }
                case OPBINDIV:
                {
                    lvmcpu.pc++;
                    MemoryNode save=Memory[lvmcpu.pc];
                    string strsave=getstring(save);
                    symbol *savesym=getsymbol(strsave);
                    lvmcpu.pc++;
                    MemoryNode mul1=Memory[lvmcpu.pc];
                    int mul1num;
                    if (mul1.value=='s')
                    {
                        string strmul1=getstring(mul1);
                        mul1num=getsymbol(strmul1)->int_value;
                    }
                    else
                        mul1num=getint(mul1);
                    lvmcpu.pc++;
                    MemoryNode mul2=Memory[lvmcpu.pc];
                    int mul2num;
                    if (mul2.value=='s') {
                        string strmul2=getstring(mul2);
                        mul2num=getsymbol(strmul2)->int_value;
                    }
                    else
                        mul2num=getint(mul2);
                    int savenum=mul1num/mul2num;
                    savesym->int_value=savenum;
                    savesym->type=int_var;
                    break;
                }
                case OPINC:
                {
                    lvmcpu.pc++;
                    int num=1;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    regoperand(regindex, add, num,parastr);
                    break;
                }
                case OPDEC:
                {
                    lvmcpu.pc++;
                    int num=1;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    regoperand(regindex, sub, num,parastr);
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
                    regoperand(regindex, cmp, num,parastr);
                    break;
                }
                case OPJG:
                {
                    lvmcpu.pc++;
                    MemoryNode cmp1=Memory[lvmcpu.pc];
                    int cmp1num;
                    //number
                    if(cmp1.value=='n')
                        cmp1num=getint(cmp1);
                    //variable
                    else
                    {
                        string symbolname=getstring(cmp1);
                        symbol *sym=getsymbol(symbolname);
                        cmp1num=sym->int_value;
                    }
                    lvmcpu.pc++;
                    MemoryNode cmp2=Memory[lvmcpu.pc];
                    int cmp2num;
                    //number
                    if(cmp2.value=='n')
                        cmp2num=getint(cmp2);
                    //variable
                    else
                    {
                        string symbolname=getstring(cmp2);
                        symbol *sym=getsymbol(symbolname);
                        cmp2num=sym->int_value;
                    }
                    lvmcpu.pc++;
                    MemoryNode addr_label=Memory[lvmcpu.pc];
                    string strlabel=getstring(addr_label);
                    int addr_value=getsymbol(strlabel)->label_addr;
                    if(lvmcpu.pc<findend(strlabel))
                    {
                        if(cmp1num>cmp2num)
                            lvmcpu.pc=addr_value-1; //at the begin the lvmcpu.pc ++;
                        else
                            lvmcpu.pc=findend(strlabel);
                    }
                    else
                    {
                        if (cmp1num>cmp2num) {
                            lvmcpu.pc=addr_value-1;
                        }
                        else
                            break;
                    }
                    break;
                }
                case OPJNG:
                {
                    lvmcpu.pc++;
                    MemoryNode cmp1=Memory[lvmcpu.pc];
                    int cmp1num;
                    //number
                    if(cmp1.value=='n')
                        cmp1num=getint(cmp1);
                    //variable
                    else
                    {
                        string symbolname=getstring(cmp1);
                        symbol *sym=getsymbol(symbolname);
                        cmp1num=sym->int_value;
                    }
                    lvmcpu.pc++;
                    MemoryNode cmp2=Memory[lvmcpu.pc];
                    int cmp2num;
                    //number
                    if(cmp2.value=='n')
                        cmp2num=getint(cmp2);
                    //variable
                    else
                    {
                        string symbolname=getstring(cmp2);
                        symbol *sym=getsymbol(symbolname);
                        cmp2num=sym->int_value;
                    }
                    lvmcpu.pc++;
                    MemoryNode addr_label=Memory[lvmcpu.pc];
                    string strlabel=getstring(addr_label);
                    symbol *label_sym=getsymbol(strlabel);
                    int addr_value=label_sym->label_addr;
                    if(lvmcpu.pc<findend(strlabel))
                    {
                        if(cmp1num<cmp2num)
                            lvmcpu.pc=addr_value-1; //at the begin the lvmcpu.pc ++;
                        else
                            lvmcpu.pc=findend(strlabel);
                    }
                    else
                    {
                        if (cmp1num<cmp2num) {
                            lvmcpu.pc=addr_value-1;
                        }
                        else
                            break;
                    }
                    break;
                }
                case OPPRINTR:
                {
                    lvmcpu.pc++;
                    MemoryNode reg=Memory[lvmcpu.pc];
                    int regindex=getregindex(reg);
                    if(regindex==3) //string
                    {
                        string str;
                        regoperand(regindex, assign, paraint, str);
                        if (str=="\\n")
                        {
                            cout<<endl;
                        }
                        else if(str=="\\s")
                        {
                            cout<<" ";
                        }
                        else
                            cout<<str;
                    }
                    else //int
                    {
                        int num;
                        regoperand(regindex, assign, num,parastr);
                        cout<<num<<endl;
                    }
                    break;
                }
                case OPPRINTRLIST:
                {
                    lvmcpu.pc++;
                    MemoryNode variable=Memory[lvmcpu.pc];
                    string var_name=getstring(variable);
                    symbol *sym=getsymbol(var_name);
                    if(sym->type==int_array)
                    {
                        for(auto value:sym->array_value)
                            cout<<value<<" ";
                    }
                    break;
                    
                }
                case OPEND:
                {
                    //segment name
                    lvmcpu.pc++;
                    break;
                }
                case OPPAUSE: 
                    break;
                default:
                    break;
            }
        }
    } while (lvmstatus==running);
}
