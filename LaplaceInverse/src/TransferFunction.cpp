#include "TransferFunction.h"
#include <fstream>
#include <ios>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include "LinearSystem.h"
using namespace std;

TransferFunction::TransferFunction(void):factors(NULL),correct_factors(NULL)
{
	
}

void TransferFunction::AddNum(void)
{
	if(factors)
	{
		delete[] factors;
		factors = NULL;
	}
	cout << "Adding numerator"<<endl;
	numerator.push_back(new LiteralElement(true));
	numerator.back()->Print();
	cout<<endl;
}



void TransferFunction::Clean(void)
{
	for(int i = 0; i < numerator.size();i++)
	{
		delete numerator[i];
	}
	for(int i = 0; i < denominator.size();i++)
	{
		delete denominator[i];
	}
	if(factors)
		delete[] factors;
}

void TransferFunction::LoadFromFile(string filename)
{
	Clean();
	ifstream in_stream(filename.c_str());

	if(!in_stream)
	{
		cout << "Could not open: "<<filename<<endl;
		exit(1) ;
	}
	cout << "Opened "<<filename<<endl;
	int n_num,max_power;
	long double coef;
	in_stream >> n_num;
	cout << "Found "<<n_num<<" numerator factors"<<endl;
	for(int num = 0; num < n_num; num++)
	{
		LiteralElement* new_num = new LiteralElement();
		in_stream >> max_power;
		for(int pow = max_power;pow >= 0;pow--)
		{
			in_stream >> coef;
			new_num->Add(new Literal(coef,pow));
		}
		numerator.push_back(new_num);
	}

	in_stream >> n_num;
	cout << "Found "<<n_num<<" denominator factors"<<endl;
	for(int num = 0; num < n_num; num++)
	{
		LiteralElement* new_num = new LiteralElement();
		in_stream >> max_power;
		for(int pow = max_power;pow >= 0;pow--)
		{
			in_stream >> coef;
			new_num->Add(new Literal(coef,pow));
		}
		denominator.push_back(new_num);
	}
	in_stream.close();
}

void TransferFunction::Interactive(void)
{
	int num,denom;
	cout << "number of numerator factors: ";
	cin >> num;
	for(int i = 0; i < num; i++)
	{
		AddNum();
	}

	cout << "number of denominator factors: ";
	cin >> denom;
	for(int i = 0; i < denom; i++)
	{
		AddDenom();
	}
}

void TransferFunction::AddDenom(void)
{
	if(factors)
	{
		delete[] factors;
		factors = NULL;
	}
	cout << "Adding denominator"<<endl;
	denominator.push_back(new LiteralElement(true));
	denominator.back()->Print();
	cout<<endl;
}

void TransferFunction::PrintFactors(void)
{
	if(factors == NULL)
	{
		cout << "Factors are not yet computed!"<<endl;
		return;
	}
	cout << "[ ";
	for(int i = 0; i < denominator.size()*2-1; i++)
	{
		cout << factors[i] << " | ";
	}

	cout << factors[denominator.size()*2-1]<<" ]";
}

void TransferFunction::NicePrintFactors(void)
{
	if(factors == NULL)
	{
		cout << "Factors are not yet computed!"<<endl;
		return;
	}
	cout << endl;
	for(int i = 0; i < denominator.size(); i++)
	{
		cout << "( ";
		if(factors[i] != 0)
		{
			cout << "A"<<i<<".s";
		}
		if(factors[i] != 0 && factors[i+1]!= 0)
		{
			cout << "+B"<<i;
		}
		else if(factors[i] == 0 && factors[i+1]!= 0)
		{
			cout << "B"<<i;
		}
		cout << " )";
		cout<<"/";denominator[i]->Print();
		if(i != denominator.size() -1)
			cout <<" + ";	
	}
	cout <<endl;
	for(int i = 0; i < denominator.size(); i++)
	{
		if(factors[i*2] != 0)
			cout << "A"<<i<<" = "<<factors[i*2]<<endl;
		if(factors[i*2+1] != 0)
			cout << "B"<<i<<" = "<<factors[i*2+1]<<endl;
	}
	cout << endl;
}

TransferFunction::~TransferFunction(void)
{
	Clean();
}

void TransferFunction::FindFactors(bool verbose)
{
	LiteralElement* final_numerator = new LiteralElement();
	final_numerator->Add(new Literal(1,0));
	LiteralElement* temp_el = NULL;
	for(int i = 0; i < numerator.size();i++)
	{
		temp_el = final_numerator;
		final_numerator = final_numerator->Multiply(numerator[i]);
		delete temp_el;
	}

	//cout << "Expanded numerator: ";final_numerator->Print(); cout << endl;
	if(verbose)
	{
		cout << "Numerator: ";
		for(int i = 0; i < numerator.size(); i++)
			numerator[i]->Print();
		cout << endl;
		cout << "Denominator: ";
		for(int i = 0; i < denominator.size(); i++)
			denominator[i]->Print();
		cout << endl;
	}
	int system_size = 0;
	for(int i = 0; i < denominator.size() ; i++)
	{
		system_size += denominator[i]->GetMaxPower();
	}
	//cout << "We will need "<<system_size<<" coefficients"<<endl;
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

			LiteralElement* p_e = elems[current_factor];
			elems[current_factor] = elems[current_factor]->Multiply(denominator[i]);
			delete p_e;
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
			linear_system.Set(i,denominator.size()*2,b_elem->coef);
	}
	
	linear_system.Solve();

	if(factors)
		delete[] factors;

	factors = new long double[denominator.size()*2];
	for(int i = 0; i < denominator.size()*2;i++)
	{
		factors[i] = linear_system.GetCoef(i);
	}

	//cleaning the remaining temporary memory
	delete final_numerator;
	for(int i = 0; i < elems.size();i++)
	{
		delete elems[i];
	}
}

void TransferFunction::TextInput(void)
{
	char line[1024]="";
	cout << "Write the numerator: ";
	
	fgets(line,1024,stdin);
	cout << "you entered: "<<line<<endl;

	cout << "Please use another method; not yet usable"<<endl;
}
