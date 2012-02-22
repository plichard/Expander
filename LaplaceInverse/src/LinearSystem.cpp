#include "LinearSystem.h"
#include <iostream>
using namespace std;

LinearSystem::LinearSystem(int size):m_size(size)
{
	m_matrix = new long double[size*(size+1)];
	if(!m_matrix)
	{
		cout << "omg epic memory fail"<<endl;
		exit(1);
	}
	memset(m_matrix,0,size*(size+1)*sizeof(long double));
}

inline const long double LinearSystem::Get(int n, int m)// line, column
{
	return m_matrix[n*(m_size+1) + m];
}

inline void LinearSystem::Set(int n, int m, long double value)
{
	m_matrix[n*(m_size+1) + m] = value;
}

void LinearSystem::Solve(void) // solve using the gauss method (Reduced echelon form)
{
	int current_line = 0;
	int current_col = 0;
	long double current_coef = 0;
	for(current_col = 0; current_col < m_size; current_col++)//we want to reduce each column
	{
		for(current_line = 0; current_line < m_size; current_line++)//lets find a suitable line
		{
			if(Get(current_line,current_col) != 0) // we found a non-null column
				break;
		}
		current_coef = Get(current_line,current_col);
		DivideLine(current_line,current_coef); //we normalize the line

		for(int i = 0; i < m_size; i++)//substract the line from every other one
		{
			if(i == current_line)
				continue;
			SubstractLine(current_line,i,Get(i,current_col));
		}
	}
}

void LinearSystem::SubstractLine(int n1, int n2, long double coef) //n1 = n1 - coef* n2
{
	for(int i = 0; i < m_size + 1;i++)
	{
		Set(n1,i,Get(n1,i)-Get(n2,i)*coef);
	}
}

void LinearSystem::DivideLine(int n, long double coef)
{
	for(int i = 0; i < m_size + 1;i++)
	{
		Set(n,i,Get(n,i)/coef);
	}
}

void LinearSystem::Add(int n, int m, long double value)
{
	Set(n,m,Get(n,m) + value);
}


LinearSystem::~LinearSystem(void)
{
	delete[] m_matrix;
}
