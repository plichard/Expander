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
	f1.AddNum();
	f1.AddDenom();
	f1.AddDenom();

	f1.FindFactors();
	return 0;
}