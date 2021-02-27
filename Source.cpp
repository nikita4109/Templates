#include <iostream>
#include "segment_tree.h"

int main()
{
	SegmentTree<int> tree(1, 10);
	for (int i = 1; i <= 10; ++i)
		tree.Add(i, 1);
	std::cout << tree(1, 10) << std::endl;

	return 0;
}
