//
//  assembler.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <string>
#include <sstream>
#include "assembler.h"
using namespace std;

Assembler::Assembler()
{
}
string Assembler::int2string(int num)
{
    stringstream s;
    string str;
    s<<num;
    s>>str;
    return str;
}
int Assembler::searchcmd(string token)
{
    int i=9;
    while (i<keynum&&strkey[i]!=token) {
        i++;
    }
    return i;
}

int Assembler::searchreg(string token)
{
    int i=0;
    while(i<9&&strkey[i]!=token)
        i++;
    return i+1;
}
tokentype Assembler::lexer(string &token,int index)
{
    tokentype type=unknow;
    int command;
    //alphabet
    if (isalpha(token[0]))
    {
        command=searchcmd(token);
        if(index+1<=codestream.size())
        {
            //address label
            if(command==keynum&&codestream[index+1]==":")
            {
                type=addr_label;
                token+=":";
            }
            else if(command==keynum&&codestream[index+1]!=":"&&codestream[index-1]!="\"")
            {
                int index;
                index=searchreg(token);
                if (index>9)
                    type=var_symbol;
                else
                    type=reg;
            }
            else if (command==keynum&&codestream[index-1]=="\""&&codestream[index+1]=="\"")
            {
                type=str;
            }
            else
            {
                type=op;
            }
        }
        //end
        else
        {
            int index;
            index=searchreg(token);
            if(index<9)
                type=reg;
            else if(index<keynum&&index>9)
                type=op;
            else
                type=var_symbol;
        }
    }
    //number
    else if (token[0]>='0'&&token[0]<='9')
    {
        type=number;
    }
    //' " '
    else if(codestream[index]=="\"")
    {
        type=quotes;
    }
    //string
    else if(codestream[index-1]=="\""&&codestream[index+1]=="\"")
    {
        type=str;
    }
    else
        type=unknow;
    return type;
}

/*
 
parameter:
    0 :undefine
    1 :define search
 
 return :
    -2  :already define
    -1  :undefine
    index : retun index
 */
int Assembler::searchsymbol(string symbolname, int sign)
{
    int index;
    for (index=0; index<symboltable.size(); index++)
    {
        if(symbolname==symboltable[index].symbolname)
            break;
    }
    if(index<symboltable.size()&&sign==0&&symboltable[index].type==addr_symbol)
    {
        cout<<"the label "<<symbolname<<"is already define "<<endl;
        return -2;
    }
    else if (index<symboltable.size()&&sign==1)
        return index;
    else
        return -1;
    
}
void Assembler::buildsymbol()
{
    int index;
    tokentype type;
    for (index=0; index<codestream.size(); index++)
    {
        string token=codestream[index];
        type=lexer(token,index);
        switch (type)
        {
            case addr_label:
                if(searchsymbol(token, 0)==-1) // not define
                {
                    symbol sym;
                    sym.symbolname=token;
                    sym.label_addr=int(index-symboltable.size()*2);
                    sym.type=addr_symbol;
                    symboltable.push_back(sym);
                }
                index++;
                break;
            case var_symbol:
            {
                if(searchsymbol(token, 0)==-1) //not define
                {
                    symbol sym;
                    sym.symbolname=token;
                    sym.define=false;
                    symboltable.push_back(sym);
                }
                break;
            }
            case unknow:
                cout<<" the label "<<token<<" is unknown "<<endl;
                break;
            default:
                break;
        }
    }
}

int Assembler::getopcode(string token)
{
    byte op=OPHALT;
    while(op<keynum&&token!=strkey[op])
        op++;
    if(op<keynum)
        return op;
    else
        return OPERROR;
}
void Assembler::assemblerrun()
{
    int operand;
    buildsymbol();
    for(int index=0;index<codestream.size();index++)
    {
        string token=codestream[index];
        tokentype type=lexer(token,index);
        switch (type) {
            case addr_label:
                index++;
                break;
            case reg:
            {
                int regindex=searchreg(token);
                string strregindex=int2string(regindex);
                MemoryNode head;
                head.value='r';
                head.next=NULL;
                MemoryNode *pointer=&head;
                for (int index=0; index<strregindex.length(); index++) {
                    MemoryNode *node=new MemoryNode;
                    node->value=strregindex[index];
                    node->next=NULL;
                    pointer->next=node;
                    pointer=node;
                }
                Memory.push_back(head);
                break;
            }
            case op:
            {
                operand=getopcode(token);
                if(operand==OPERROR)
                    cout<<" error operand "<<token<<endl;
                MemoryNode head;
                head.value='o';
                head.next=NULL;
                int opindex=searchcmd(token);
                Mempointer++;
                string key=int2string(opindex);
                MemoryNode *pointer=&head;
                for(int index=0;index<key.length();index++)
                {
                    MemoryNode *node=new MemoryNode;
                    node->value=key[index];
                    node->next=NULL;
                    pointer->next=node;
                    pointer=node;
                }
                Memory.push_back(head);
                break;
            }
            case var_symbol:
            {
                MemoryNode head;
                string var=token;
                head.value='v';
                head.next=NULL;
                MemoryNode * pointer=&head;
                for(int index=0;index<var.length();index++)
                {
                    MemoryNode *node=new MemoryNode;
                    node->value=var[index];
                    node->next=NULL;
                    pointer->next=node;
                    pointer=node;
                }
                Memory.push_back(head);
                break;
            }
            case str:
            {
                MemoryNode head;
                head.value='s';
                head.next=NULL;
                MemoryNode *pointer=&head;
                for (int index=0; index<token.length(); index++) {
                    MemoryNode *node=new MemoryNode;
                    node->value=token[index];
                    node->next=NULL;
                    pointer->next=node;
                    pointer=node;
                }
                Memory.push_back(head);
                break;
            }
            case number:
            {
                MemoryNode head;
                head.value='n';
                head.next=NULL;
                MemoryNode *pointer=&head;
                for (int index=0; index<token.length(); index++) {
                    MemoryNode *node=new MemoryNode;
                    node->value=token[index];
                    node->next=NULL;
                    pointer->next=node;
                    pointer=node;
                }
                Memory.push_back(head);
                break;
            }
            default:
                break;
        }
    }
    cout<<"Assembler is running successfully ..."<<endl;
}
