#pragma once
#include "Literal.h"
#include <map>
#include <vector>

typedef std::map<unsigned int,Literal*> LiteralMap;
typedef LiteralMap::iterator LiteralMapIt;

class LiteralElement
{
public:
	explicit LiteralElement(bool interactive = false);
	~LiteralElement(void);
	Literal* Get(unsigned int index)
	{
		return elements.at(index);
	}
	unsigned int Size(void)
	{
		return elements.size();
	}

	void Print(void);

	void Add(Literal* l)
	{
		LiteralMapIt it = elements.find(l->power);
		if(it == elements.end())
			elements[l->power] = l;
		else
			elements[l->power] = new Literal(it->second->coef+l->coef,l->power,l,it->second);
	}

	const int GetMaxPower(void);

	void Simplify(void)
	{
		std::vector<int> to_erase;
		for(LiteralMapIt it = elements.begin();it!=elements.end();it++)
		{
			if(it->second->coef == 0)
				to_erase.push_back(it->first);
		}
		for(std::vector<int>::iterator it = to_erase.begin(); it != to_erase.end();it++)
			elements.erase(*it);
	}

	void ChangePower(int d_power);

	LiteralElement* operator*(LiteralElement& l2)
	{
		LiteralElement* result = new LiteralElement(false);
		for(LiteralMapIt it1 = elements.begin();it1 != elements.end();it1++)
		{
			for(LiteralMapIt it2 = l2.elements.begin();it2 != l2.elements.end();it2++)
			{

				result->Add((*(it1->second))*(*(it2->second)));
			}
		}
		result->Simplify();
		return result;
	}

	void operator*=(LiteralElement& l2)
	{
		for(LiteralMapIt it1 = elements.begin();it1 != elements.end();it1++)
		{
			for(LiteralMapIt it2 = l2.elements.begin();it2 != l2.elements.end();it2++)
			{

				this->Add((*(it1->second))*(*(it2->second)));
			}
		}
		this->Simplify();
	}

protected:
	//std::vector<Literal*> elements; //all elements in basic denominator
	std::map<unsigned int,Literal*> elements;
};

