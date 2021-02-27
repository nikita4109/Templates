#include <iostream>

template<typename T>
class segment_tree
{
	public:

	segment_tree(T l, T r)
	{
		left = l;
		right = r;
		sum = 0;

		if (l != r)
		{
			int middle = (l + r) / 2;
			leftVertex = new segment_tree(l, middle);
			rightVertex = new segment_tree(middle + 1, r);
		}
	}

	void add(int position, T value)
	{
		sum += value;

		if (leftVertex)
		{
			int middle = (left + right) / 2;
			if (middle >= position)
				leftVertex->add(position, value);
			else
				rightVertex->add(position, value);
		}
	}

	T get(int l, int r)
	{
		if (left > r || right < l) return 0;
		if (left >= l && right <= r) return sum;

		return leftVertex->get(l, r) + rightVertex->get(l, r);
	}

	private:

		int left, right, sum;
		segment_tree *leftVertex = 0, *rightVertex = 0;
};
