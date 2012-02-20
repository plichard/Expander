#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "TransferFunction.h"
#include "Literal.h"

typedef map<string,TransferFunction*> TransferMap;
typedef TransferMap::iterator TransferMapIt;

TransferMap functions;

int main(int argc, char **argv)
{
	Literal *l1 = new Literal(2,0);
	Literal *l2 = new Literal(4,2);

	Literal* l3 = (*l1)*(*l2);

	return 0;
}