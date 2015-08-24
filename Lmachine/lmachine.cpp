//
//  lmachine.cpp
//  Lmachine
//
//  Created by leviathan on 15/8/21.
//  Copyright (c) 2015年 leviathan. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <cstdio>
#include "lmachine.h"
using namespace std;
#define file "sum.txt"
Lmachine::Lmachine()
{
    
}
//init static variable
string Lmachine::infile="";
string Lmachine::outfile="";

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