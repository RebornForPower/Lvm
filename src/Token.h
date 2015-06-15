#pragma once
#include <iostream>
#include <string>
using namespace std;
class Token
{
	public:
		Token();
		Token(int number);
		Token(string ID);
		bool IsID;
		bool IsNumber;
		int Number;
		string ID;
		string GetID();
		int GetNumber();
};

