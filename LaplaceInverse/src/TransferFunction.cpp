#include "TransferFunction.h"
#include <iostream>
using namespace std;

TransferFunction::TransferFunction(void)
{
	
}

void TransferFunction::AddNum(void)
{
	cout << "Adding numerator"<<endl;
	numerator.push_back(new LiteralElement(true));
	numerator.back()->Print();
	cout<<endl;
}

void TransferFunction::AddDenom(void)
{
	cout << "Adding denominator"<<endl;
	denominator.push_back(new LiteralElement(true));
	denominator.back()->Print();
	cout<<endl;
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

void TransferFunction::FindFactors(void)
{
	LiteralElement* final_numerator = new LiteralElement();
	final_numerator->Add(new Literal(1,0));
	for(int i = 0; i < numerator.size();i++)
	{
		final_numerator = (*final_numerator)*(*numerator[i]);
	}

	cout << "Expanded numerator: ";final_numerator->Print(); cout << endl;
	cout << "Denominator: ";
	for(int i = 0; i < denominator.size(); i++)
		denominator[i]->Print();
	cout << endl;
	cout << "We will need "<<denominator.size()<<" coefficients"<<endl;
	
}