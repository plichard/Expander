#include "LinearSystem.h"
#include <iostream>
using namespace std;

LinearSystem::LinearSystem(int size):m_size(size)
{
	m_matrix = new long double[size*(size+1)];
	if(!m_matrix)
	{
		cout << "omg epic memory fail"<<endl;
	}
}

const long double LinearSystem::Get(int n, int m)// line, column
{
	return m_matrix[n*(m_size+1) + m];
}

void LinearSystem::Set(int n, int m, long double value)
{
	m_matrix[n*(m_size+1) + m] = value;
}

void LinearSystem::Solve(void) // solve using the gauss method (Reduced echelon form)
{
	for(int var =  0 ; var < m_size; var++)
	{

	}
}


LinearSystem::~LinearSystem(void)
{
}
