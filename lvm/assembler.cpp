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
    if (isalpha(token[0]))
    {
        command=searchcmd(token);
        if(index+1<=codestream.size())
        {
            if(command==keynum&&codestream[index+1]==":")
            {
                    type=label;
                    token+=":";
            }
            else if(command==keynum&&codestream[index]!=":")
            {
                int index;
                index=searchreg(token);
                if (index>9)
                    type=reflabel;
                else
                    type=reg;
            }
            else
            {
                type=op;
            }
        }
        else
        {
            int index;
            index=searchreg(token);
            if(index<9)
                type=reg;
            else if(index<keynum&&index>9)
                type=op;
            else
                type=reflabel;
        }
    }
    else if (token[0]>='0'&&token[0]<='9')
    {
        type=number;
    }
    else
        type=unknow;
    return type;
}

/*
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
    if(index<symboltable.size()&&sign==0)
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
            case label:
                if(searchsymbol(token, 0)==-1) //not define
                {
                    symbol sym;
                    sym.symbolname=codestream[index];
                    sym.symboladdr=int(index-symboltable.size()*2);
                    sym.first=NULL;
                    symboltable.push_back(sym);
                }
                index++;
                break;
            case reflabel:
            {
                int symbolindex=searchsymbol(token,1);
                if(symbolindex==-1)
                {
                    //undefine
                    continue;
                }
                else
                {
                    refsymbol *newsymbol=new refsymbol;
                    newsymbol->refsymboladdr=symbolindex;
                    newsymbol->next=NULL;
                    if(symboltable[symbolindex].first==NULL)
                        symboltable[symbolindex].first=newsymbol;
                    else
                    {
                        refsymbol * ref=symboltable[symbolindex].first;
                        refsymbol *refnode=ref;
                        while (ref!=NULL)
                        {
                            refnode=ref;
                            ref=ref->next;
                        }
                        refnode->next=newsymbol;
                    }
                }
                break;
            }
            case unknow:
                cout<<" the label"<<token<<" is unknown "<<endl;
                break;
            default:
                break;
        }
    }
}

int Assembler::getopcode(string token)
{
    byte op=OpHALT;
    while(op<keynum&&token!=strkey[op])
        op++;
    if(op<keynum)
        return op;
    else
        return OpERROR;
}
void Assembler::assemblerrun()
{
    int labelindex=0;
    int operand;
    buildsymbol();
    for(int index=0;index<codestream.size();index++)
    {
        string token=codestream[index];
        tokentype type=lexer(token,index);
        switch (type) {
            case label:
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
                if(operand==OpERROR)
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
            case reflabel:
                labelindex=searchsymbol(token,1);
                if (labelindex==-1) {
                    cout<<" no such  a label"<<endl;
                }
                else
                {
                    MemoryNode head;
                    string addr=int2string(symboltable[labelindex].symboladdr);
                    head.value=addr[0];
                    head.next=NULL;
                    MemoryNode * pointer=&head;
                    for(int index=1;index<addr.length();index++)
                    {
                        MemoryNode *node=new MemoryNode;
                        node->value=addr[index];
                        node->next=NULL;
                        pointer->next=node;
                        pointer=node;
                    }
                    Memory.push_back(head);
                }
                break;
            case number:
                {
                    MemoryNode head;
                    head.value=token[0];
                    head.next=NULL;
                    MemoryNode *pointer=&head;
                    for (int index=1; index<token.length(); index++) {
                        MemoryNode *node=new MemoryNode;
                        node->value=token[index];
                        node->next=NULL;
                        pointer->next=node;
                        pointer=node;
                    }
                    Memory.push_back(head);
                }
            default:
                break;
        }
    }
    cout<<"Assembler is running successfully ..."<<endl;
}
