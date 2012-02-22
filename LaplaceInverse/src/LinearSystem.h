#pragma once
class LinearSystem
{
public:
	LinearSystem(int size); //only one dimension is required; we assume we have n variables and n equations
	~LinearSystem(void);
	inline const long double Get(int n, int m); // line, column
	inline void Set(int n, int m, long double value);
	void Add(int n, int m, long double value);
	void Solve(void);
	

private:
	long double *m_matrix;
	int m_size;
	void SubstractLine(int n1,int n2,long double coef); //n1 = n1 - coef* n2
	void DivideLine(int n,long double coef);
};

