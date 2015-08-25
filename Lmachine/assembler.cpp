//
//  assembler.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <string>
#include "assembler.h"
using namespace std;

Assembler::Assembler()
{
}

int Assembler::searchcmd(string token)
{
    int i=0;
    while (i<opnum&&strop[i]!=token) {
        i++;
    }
    return i;
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
            if(command==opnum&&codestream[index+1]==":")
            {
                    type=label;
                    token+=":";
            }
            else if(command==opnum&&codestream[index]!=":")
            {
                for(int num=0;num<=regnum;num++)
                {
                    if (stringregister[num]==token)
                    {
                        type=reg;
                        break;
                    }
                    else
                        type=reflabel;
                }
            }
            else
            {
                type=op;
            }
        }
        else
        {
            for(int num=0;num<=regnum;num++)
            {
                if (stringregister[num]==token)
                {
                    type=reg;
                    return type;
                }
            }
            if(command<opnum)
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
                    sym.symboladdr=index;
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

byte Assembler::getopcode(string token)
{
    byte op=OpHALT;
    while(op<opnum&&token!=strop[op])
        op++;
    if(op<opnum)
        return op;
    else
        return OpERROR;
}
void Assembler::assemblerrun()
{
    int labelindex=0;
    byte operand;
    byte mempointer;
    buildsymbol();
    for(int index=0;index<codestream.size();index++)
    {
        string token=codestream[index];
        tokentype type=lexer(token,index);
        switch (type) {
            case op:
                operand=getopcode(token);
                if(operand==OpERROR)
                    cout<<" error operand "<<token<<endl;
                    memory[mempointer]=operand;
                mempointer++;
                break;
            case reflabel:
                token+=":";
                labelindex=searchsymbol(token,1);
                if (labelindex==-1) {
                    cout<<" no such  a label"<<endl;
                }
                else
                {
                    memory[mempointer]=symboltable[labelindex].symboladdr;
                    mempointer++;
                }
                break;
            case number:
                {
                    int number=atoi(codestream[index].c_str());
                    memory[mempointer]=number;
                    break;
                }
            default:
                break;
        }
    }
}
