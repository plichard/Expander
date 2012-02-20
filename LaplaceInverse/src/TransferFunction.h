#pragma once
#include "LiteralElement.h"
#include <vector>

typedef std::vector<LiteralElement*> ElementVec;
typedef ElementVec::iterator ElementVecIt;

class TransferFunction
{
public:
	TransferFunction(void);
	~TransferFunction(void);
	void AddNum(void);
	void AddDenom(void);
	void FindFactors(void);

private:
	ElementVec numerator;
	ElementVec denominator;
	ElementVec factors;
};

