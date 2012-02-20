#include "LiteralElement.h"
#include <iostream>
#include <cstdio>
using namespace std;

LiteralElement::LiteralElement(void)
{
	int exp = 0;
	int max_exp = 0;
	long double coef;
	cout << "max exp: ";
	cin >> max_exp;
	for(int exp = max_exp;exp>=0;exp--)
	{
		cout<<"s^"<<exp<<"*: ";
		cin >> coef;
		Add(new Literal(coef,exp));
	}
	Simplify();
}

LiteralElement::~LiteralElement(void)
{
}

void LiteralElement::Print(void)
{
	char coef_buffer[32];
	char var_buffer[2];
	char exp_buffer[32];
	char sign_buffer[2];

	cout << "(";
	for(LiteralMapIt it = elements.begin(); it != elements.end();it++)
	{
		if(it->first == 0) //power == 0
		{
			sprintf(var_buffer,"");
			sprintf(exp_buffer,"");
		}
		else if(it->first == 1) //power == 1
		{
			sprintf(var_buffer,"s");
			sprintf(exp_buffer,"");
		}
		else //power > 1
		{
			sprintf(var_buffer,"s");
			sprintf(exp_buffer,"^%d",it->first);
		}
		if(it->second->coef > 0)
			sprintf(sign_buffer,"+");
		else
			sprintf(sign_buffer,"");

		if(it->second->coef == 1)
			sprintf(coef_buffer,"");
		else
			sprintf(coef_buffer,"%1.0lf",it->second->coef);

		cout<<sign_buffer<<coef_buffer<<var_buffer<<exp_buffer;
	}
	cout<< ")";
}
