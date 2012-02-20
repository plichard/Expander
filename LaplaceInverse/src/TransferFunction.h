#pragma once
#include "Factor.h"
#include <vector>

typedef std::vector<Factor*> FactorVec;
typedef FactorVec::iterator FactorVecIt;

class TransferFunction
{
public:
	TransferFunction(void);
	~TransferFunction(void);
	void AddNum(void);
	void AddDenom(void);
private:
	FactorVec numerator;
	FactorVec denominator;
};

