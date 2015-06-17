#include "Token.h"
using namespace std;
Token::Token()
{

}
Token::Token(int number)
{
	this->Number = number;
	this->IsNumber = true;
	this->IsID = false;
}
Token::Token(string ID)
{
	this->ID = ID;
	this->IsID = true;
	this->IsNumber = false;
}
string Token::GetID()
{
	return this->ID;
}
int Token::GetNumber()
{
	return this->Number;
}