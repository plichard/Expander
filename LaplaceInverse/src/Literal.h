#pragma once
#include <cstdlib>
class Literal
{
public:
	static int object_count;

	explicit Literal(void):coef(0),power(0){object_count++;;}
	explicit Literal(long double coef,unsigned int power,Literal* parent1 = NULL,Literal* parent2 = NULL):coef(coef),power(power)
	{
		object_count++;
		if(parent1)
			delete parent1;
		if(parent2)
			delete parent2;
	}
	~Literal(void);
	long double coef;
	unsigned int power;
	void operator*=(Literal& l2)
	{
		this->power += l2.power;
		this->coef *= l2.coef;
	}

	Literal* operator*(Literal& l2)
	{
		return new Literal(this->coef*l2.coef,this->power+l2.power,this,&l2);
	}

	Literal* Multiply(Literal* l2,bool keep = true)
	{
		return new Literal(this->coef*l2->coef,this->power+l2->power,NULL,NULL);
	}
};

