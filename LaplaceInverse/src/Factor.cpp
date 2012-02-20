#include "Factor.h"
#include <iostream>
using namespace std;

Factor::Factor(void):degree(0),root(0),constant(0)
{
	cout << "Degree(1,2): ";
	cin >> degree;
	if(degree == 2)
	{
		cout << "Root: ";
		cin >> root;
	}
	cout << "Constant: ";
	cin >> constant;
}

void Factor::Print(void)
{
	cout<<"( ";
	switch(degree)
	{
	case 0:
		cout << constant;
		break;
	case 1:
		if(constant == 0)
			cout << "s";
		else
			cout<< "s + "<<constant;
		break;
	case 2:
		if(root == 0)
			cout << "s^2 ";
		else
			cout << "(s + "<<root<<" )^2 ";
		if(constant != 0)
			cout << "+ "<<constant;
		break;
	}
	cout<<" )";
}

Factor::~Factor(void)
{
}
