#include <iostream>
#include "mint.h"

int main()
{
	mint a = 5;
	if (a) a = 1;
	std::cout << a << std::endl;

	return 0;
}
