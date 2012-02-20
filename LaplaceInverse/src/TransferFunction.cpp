#include "TransferFunction.h"
#include <iostream>
using namespace std;

TransferFunction::TransferFunction(void)
{
	
}

void TransferFunction::AddNum(void)
{
	numerator.push_back(new Factor());
	numerator.back()->Print();
	cout<<endl;
}

void TransferFunction::AddDenom(void)
{
	denominator.push_back(new Factor());
}


TransferFunction::~TransferFunction(void)
{
	for(int i = 0; i < numerator.size();i++)
	{
		delete numerator[i];
	}
	for(int i = 0; i < denominator.size();i++)
	{
		delete denominator[i];
	}
}
