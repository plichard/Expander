#include "LiteralElement.h"
#include <iostream>
using namespace std;

LiteralElement::LiteralElement(void)
{
}

LiteralElement::~LiteralElement(void)
{
}

void LiteralElement::Print(void)
{
	cout<<"(";
	for(LiteralMapIt it = elements.begin(); it != elements.end();it++)
	{
		if(it->first == 0) //if the power == 0
			cout<<it->second->coef<<" ";
		else
			cout<<it->second->coef<<"s^"<<it->first<<" ";
	}
	cout << ")";
}
