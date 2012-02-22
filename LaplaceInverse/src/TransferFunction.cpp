#include "TransferFunction.h"
#include <iostream>
#include "LinearSystem.h"
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
		final_numerator = final_numerator->Multiply(numerator[i]);
	}

	cout << "Expanded numerator: ";final_numerator->Print(); cout << endl;
	cout << "Denominator: ";
	for(int i = 0; i < denominator.size(); i++)
		denominator[i]->Print();
	cout << endl;
	cout << "We will need "<<denominator.size()<<" coefficients"<<endl;
	LinearSystem linear_system(denominator.size()*2);

	
	ElementVec elems(denominator.size());
	for(int i = 0 ; i < elems.size() ; i++)
	{
		elems[i] = new LiteralElement();
		elems[i]->Add(new Literal(1,0));
	}

	for(int current_factor = 0; current_factor < denominator.size(); current_factor++)
	{
		for(int i = 0; i < denominator.size();i++) // create the expanded factor for a "As + B" coef
		{
			if(i == current_factor) // we want to exclude the current factor, obviously
				continue;
			elems[i] = elems[i]->Multiply(denominator[i]);
		}
	}

	Literal* temp = NULL;
	for(int i = 0; i < denominator.size(); i++) // we loop through every expanded factor
	{
		for(int pow = 0; pow < denominator.size()*2;pow++)
		{
			temp = elems[i]->Get(pow);
			if(!temp)
				continue;
			
			linear_system.Add(pow+1,i*2,temp->coef); //factor multiplied by As, power increases by 1
			linear_system.Add(pow,i*2+1,temp->coef); // factor multiplied by B
		}
		if(denominator[i]->GetMaxPower() < 2)
			linear_system.SetNullCoefs(i*2);
	}

	for(int i = 0; i <= final_numerator->GetMaxPower(); i++)
	{
		Literal* b_elem = final_numerator->Get(i);
		if(b_elem)
		{
			cout << "Setting b_coef "<<b_elem->coef<<endl;
			linear_system.Set(i,denominator.size()*2,b_elem->coef);
		}
	}

	cout << "Before solving:"<<endl;
	linear_system.Print();
	linear_system.Solve();
	cout << "After solving:"<<endl;
	linear_system.Print();
}