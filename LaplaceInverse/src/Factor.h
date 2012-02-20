#pragma once

class Complex
{
public:
	Complex(long double a,long double b):a(a),b(b){}
	long double a,b; //as in a + bi
};


class Factor
{
public:
	Factor(void);
	~Factor(void);
	void Print(void);
	Complex Null(void); // returns the (possibly)
private:
	int degree;
	long double root;
	long double constant;
};



