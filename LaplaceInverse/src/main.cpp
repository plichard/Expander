#include <iostream>
#include <string>
#include <map>
#include <cstdio>
using namespace std;
#include "TransferFunction.h"
#include "Literal.h"
#include "LiteralElement.h"
#include "MemoryManager.h"

typedef map<string,TransferFunction*> TransferMap;
typedef TransferMap::iterator TransferMapIt;

TransferMap functions;

int main(int argc, char **argv)
{
	/*
	cout << "Lets test the memory manager"<<endl;
	MemoryManager<LiteralElement> mem(10);
	LiteralElement* elem0 = mem.New();
	LiteralElement* elem1 = mem.New();
	LiteralElement* elem2 = mem.New();
	LiteralElement* elem3 = mem.New();
	mem.Free(elem2);
	mem.Free(elem1);
	elem2 = mem.New();*/
	cout << "Your system supports "<<sizeof(long double)*8<<"bit precision"<<endl;

	int choice;
	TransferFunction* f1 = new TransferFunction;
	//f1.TextInput();
	cout << "Interactive or from file(0,1): ";
	cin >> choice;

	if(choice == 1)
	{
		string filename;
		cout << "File to load:";
		cin >> filename;

		f1->LoadFromFile(filename);
	}
	else if(choice == 0)
		f1->Interactive();
	else
	{
		cout << "Unkown choice, exiting."<<endl;
		exit(0);
	}

	/*
	int max_loop = 1000;
	int bar_size = 20;
	cout << "[";
	for(int i = 0; i < max_loop; i++)
	{
		if(!(i%(max_loop/bar_size)))
			cout<<"=";fflush(stdout);
		f1->FindFactors(false);
	}
	cout << "]"<<endl;*/
	f1->FindFactors();
	

	cout << "Factors: "; f1->PrintFactors(); cout << endl;
	f1->NicePrintFactors();
	delete f1;
	cout << "memory stats(lost objects): "<<endl;
	cout << "LiteralElement: "<<LiteralElement::object_count<<endl;
	cout << "Literal       : "<<Literal::object_count<<endl;
	
	return 0;
}
