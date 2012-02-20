#include <iostream>
#include <string>
#include <map>
using namespace std;
#include "TransferFunction.h"

typedef map<string,TransferFunction*> TransferMap;
typedef TransferMap::iterator TransferMapIt;

TransferMap functions;

int main(int argc, char **argv)
{
	string command = "";
	string arg = "";
	TransferFunction test;
	test.AddNum();
	test.AddNum();

	








	return 0;
}