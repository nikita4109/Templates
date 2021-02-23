#include <iostream>
#include "segment_tree.h"

int main()
{
	segment_tree tree(1, 10);

	for (int i = 1; i <= 10; ++i)
		tree.add(i, 1);

	for (int i = 1; i <= 10; ++i)
		std::cout << tree.get(i, i) << " ";
	std::cout << std::endl;

	return 0;
}
