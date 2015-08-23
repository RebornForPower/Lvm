//
//  lmachine.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "lmachine.h"
using namespace std;

Lmachine::Lmachine()
{
    
}
//init static variable
string Lmachine::infile="";
string Lmachine::outfile="";

bool Lmachine::init()
{
    cout<<" input file :";
    cin>>infile;
    fstream search;
    search.open(string2char(infile));
    if(!search)
        cout<<"file "<<infile<<" not find "<<endl;
    while (!search) {
        cin>>infile;
        search.open(string2char(infile));
    }
    cout<<" output file :";
    cin>>outfile;
    return true;
}

char * Lmachine::string2char(string str)
{
    return const_cast<char *>(str.c_str());
}

void Lmachine::readline()
{
    int index,length;
    ifstream code;
    string line;
    code.open(string2char(Lmachine::infile));
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
                }
                codestream.push_back(token);
            }
            //id
            else if((line[index]>='a'&&line[index]<'z')||(line[index]>='A'&&line[index]<='Z'))
                {
                    string token="";
                    token+=line[index];
                    while ((line[index]>='a'&&line[index]<'z')||(line[index]>='A'&&line[index]<='Z')||(line[index]>='0'&&line[index]<'9')) {
                        token+=line[index];
                    }
                
                }
            //comments
            else if (line[index]=='#')
            {
                index++;
                while (line[index]!='\n') {
                    index++;
                }
            }
            // " : " sign
            else if(line[index]==':')
            {
                string token="";
                token=line[index];
            }
        }
    }
}