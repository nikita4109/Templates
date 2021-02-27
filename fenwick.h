#include <vector>
#include <iostream>

template<typename T>
class Fenwick
{
public:

	Fenwick(int len)
	{
		length = len;
		tree = std::vector<T>(length + 1, 0);
	}

	T operator () (int left, int right)
	{
		std::cout << left << " " << right << std::endl;
		return getSum(right) - getSum(left - 1);
	}

	void Add(int position, T value)
	{
		for (; position <= length; position += position & -position)
			tree[position] += value;
	}

	size_t Size() const { return length; }

private:
	size_t length;
	std::vector<T> tree;

	T getSum(int r)
	{
		T result = 0;
		for (; r > 0; r -= r & -r)
			result += tree[r];
		return result;
	}
};
