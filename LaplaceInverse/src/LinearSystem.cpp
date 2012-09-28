
#include "LinearSystem.h"
#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

LinearSystem::LinearSystem(int size):m_size(size),m_null_coefs(0)
{
	m_matrix = new long double[(size+size/2)*(size+1)]; //we add size/2 for all the possible null coefs, maybe not the most optimal method, but it works
	if(!m_matrix)										// +1 column for the result side of the system
	{
		cout << "omg epic memory fail"<<endl;
		exit(1);
	}
	memset(m_matrix,0,(size+size/2)*(size+1)*sizeof(long double));
}

inline const long double LinearSystem::Get(int n, int m)// line, column
{
	return m_matrix[n*(m_size+1) + m];
}



void LinearSystem::SetNullCoefs(int m)
{
	Set(m_size + m_null_coefs,m,1);
	m_null_coefs++;
}

long double LinearSystem::GetCoef(int m)
{
	for(int i = 0; i < m_size*1.5;i++)
	{
		if(Get(i,m) == 1)
			return Get(i,m_size);
	}
	return 0;
}

void LinearSystem::Solve(void) // solve using the gauss method (Reduced echelon form)
{
	printf_s("solve started\n");
	bool* used_line = new bool[m_size];
	memset(used_line,false,m_size*sizeof(bool));
	int current_line = 0;
	int current_col = 0;
	long double current_coef = 0;
	for(current_col = 0; current_col < m_size; current_col++)//we want to reduce each column
	{
		int suitable_line = -1;
		//cout << "Looking for the '"<<current_col<<"' column candidate"<<endl;
		for(current_line = 0; current_line < m_size*1.5; current_line++)//lets find a suitable line
		{
			bool non_null = false;
			if(Get(current_line,current_col) != 0) // we found a non-null column
			{
				for(int col = 0; col < current_col; col++) // check that the line is null before the colum value
				{
					if(Get(current_line,col) != 0)
					{
						non_null = true;
					}
				}
				if(non_null)
					continue;
				suitable_line = current_line;
				//cout << "Found: "<<current_line<<endl;
				break;
			}
		}
		if(suitable_line == -1)
		{
			cout << "Could not find a suitable line :S"<<endl;
			exit(1);
		}
		current_coef = Get(current_line,current_col);
		DivideLine(current_line,current_coef); //we normalize the line

		for(int i = 0; i < m_size*1.5; i++)//substract the line from every other one
		{
			if(i == current_line)
				continue;

			if(Get(i,current_col) == 0)
				continue;
			SubstractLine(i,current_line,Get(i,current_col));
			//Print();
		}
	}
}

void LinearSystem::SubstractLine(int n1, int n2, long double coef) //n1 = n1 - coef* n2
{
	//cout << "substracting "<<n2<<"*"<<coef<<" from "<<n1<<endl;
	for(int i = 0; i < m_size + 1;i++)
	{
		Set(n1,i,Get(n1,i)-Get(n2,i)*coef);
	}
}

void LinearSystem::Print(void)
{
	cout<<endl<<"==============="<<endl;
	
	for(int y = 0; y <m_size+m_size/2; y++)
	{
		for(int x = 0; x < m_size+1;x++)
		{
			cout<<Get(y,x)<<" ";
		}
		cout<<endl;
	}
	cout<<endl<<"==============="<<endl;
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
	//cout << "adding "<<value<<" to line "<<n<<endl;
	Set(n,m,Get(n,m) + value);
}


LinearSystem::~LinearSystem(void)
{
	delete[] m_matrix;
}

