#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "TransferFunction.h"
#include "Literal.h"
#include "LiteralElement.h"

typedef map<string,TransferFunction*> TransferMap;
typedef TransferMap::iterator TransferMapIt;

TransferMap functions;

int main(int argc, char **argv)
{
	TransferFunction f1;
	int num,denom;
	cout << "number of numerator factors: ";
	cin >> num;
	for(int i = 0; i < num; i++)
	{
		f1.AddNum();
	}

	cout << "number of denominator factors: ";
	cin >> denom;
	for(int i = 0; i < denom; i++)
	{
		f1.AddDenom();
	}

	f1.FindFactors();
	cout << "Factors: "; f1.PrintFactors(); cout << endl;
	return 0;
}