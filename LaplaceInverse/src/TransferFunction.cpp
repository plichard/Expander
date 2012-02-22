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
		final_numerator = (*final_numerator)*(*numerator[i]);
	}

	cout << "Expanded numerator: ";final_numerator->Print(); cout << endl;
	cout << "Denominator: ";
	for(int i = 0; i < denominator.size(); i++)
		denominator[i]->Print();
	cout << endl;
	cout << "We will need "<<denominator.size()<<" coefficients"<<endl;
	LinearSystem linear_system(denominator.size()*2);

	
	ElementVec elems(denominator.size());
	for(int current_factor = 0; current_factor < denominator.size(); current_factor++)
	{
		for(int i = 0; i < denominator.size();i++) // create the expanded factor for a "As + B" or "A" coef
		{
			if(i == current_factor)
				continue;
			elems[i] = (*elems[i])*(*denominator[i]);
		}
	}
	LiteralElement var_elem;
	var_elem.Add(new Literal(1,1));

	for(int i = 0; i < denominator.size(); i++)
	{
		for(int pow = 0; pow < denominator.size()*2-2;pow++) // -2: we ommit one factor
		{
			Literal* temp = elems[i]->Get(pow);
			if(!temp)
				continue;
			
			linear_system.Add(pow+1,i*2,temp->coef);
			linear_system.Add(pow,i*2+1,temp->coef);
		}
	}
}