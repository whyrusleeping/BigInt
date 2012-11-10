#include "bigint.h"
#include <iostream>

using std::cout;

int main()
{
	bigint::Init();


	bigint a;
	bigint b;

	a = 15;
	b = 27;

	bigint c = a * b;

	c.print();

	return 0;
}
