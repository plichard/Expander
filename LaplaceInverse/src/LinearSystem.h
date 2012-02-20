#pragma once
class LinearSystem
{
public:
	LinearSystem(int size); //only one dimension is required; we assume we have n variables and n equations
	~LinearSystem(void);
	const long double Get(int n, int m); // line, column
	void Set(int n, int m, long double value);
	void Solve(void);
private:
	long double *m_matrix;
	int m_size;
};

