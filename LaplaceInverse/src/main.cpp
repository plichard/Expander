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
	cout << "Your system supports "<<sizeof(long double)*8<<"bit precision"<<endl;

	int choice;
	TransferFunction f1;
	//f1.TextInput();
	cout << "Interactive or from file(0,1): ";
	cin >> choice;

	if(choice == 1)
	{
		string filename;
		cout << "File to load:";
		cin >> filename;

		f1.LoadFromFile(filename);
	}
	else if(choice == 0)
		f1.Interactive();
	else
	{
		cout << "Unkown choice, exiting."<<endl;
		exit(0);
	}
	f1.FindFactors();

	cout << "Factors: "; f1.PrintFactors(); cout << endl;
	f1.NicePrintFactors();
	
	return 0;
}
