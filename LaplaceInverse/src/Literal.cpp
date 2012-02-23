#include "Literal.h"


Literal::~Literal(void)
{
	object_count--;
}

int Literal::object_count = 0;
