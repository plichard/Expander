#include "LiteralElement.h"
#include <iostream>
#include <cstdio>
using namespace std;

LiteralElement::LiteralElement(bool interactive)
{
	object_count++;;
	if(!interactive)
		return;
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

const int LiteralElement::GetMaxPower(void)
{
	int max = 0;
	for(LiteralMapIt it = elements.begin(); it != elements.end(); it++)
	{
		if(it->first > max)
			max = it->first;
	}
	return max;
}

LiteralElement::~LiteralElement(void)
{
	object_count--;
	for(LiteralMapIt it = elements.begin(); it != elements.end();it++)
	{
		delete it->second;
	}
}

void LiteralElement::ChangePower(int d_power)
{
	for(LiteralMapIt it = elements.begin(); it != elements.end(); it++)
	{
		it->second->power++;
	}
}

void LiteralElement::UglyPrint(void)
{
	cout << "(";
	for(LiteralMapIt it = elements.begin(); it != elements.end();it++)
	{
		
	}
	cout<< ")";
}

void LiteralElement::Print(void)
{
	char coef_buffer[32];
	char var_buffer[2];
	char exp_buffer[32];
	char sign_buffer[2];

	cout << "(";
	for( int i = GetMaxPower();i >= 0;i--)
	{
		LiteralMapIt it = elements.find(i);
		if(it == elements.end())
			continue;
	//for(LiteralMapIt it = elements.begin(); it != elements.end();it++)
	//{
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

		if(it->second->coef == 1 && it->first == 0)
			sprintf(coef_buffer,"1");
		else if(it->second->coef == 1)
			sprintf(coef_buffer,"");
		else
			sprintf(coef_buffer,"%Lf",it->second->coef); //%1.0Lf

		if(it->second->coef == 0)
		{
			sprintf(var_buffer,"");
			sprintf(coef_buffer,"");
		}

		cout<<sign_buffer<<coef_buffer<<var_buffer<<exp_buffer;
	}
	cout<< ")";
}

int LiteralElement::object_count = 0;
