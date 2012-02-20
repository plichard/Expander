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
	LiteralElement elem1;

	
	elem1.Print();cout<<endl;
	return 0;
}