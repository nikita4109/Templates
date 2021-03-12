#include <memory>

template<typename T>
class SegmentTree
{
	public:

	SegmentTree(T l, T r)
	{
		left = l;
		right = r;
		sum = 0;
	}

	void Add(int position, T value)
	{
		sum += value;

		if (left != right)
		{
			if (!leftVertex)
				createChildren();

			int middle = (left + right) / 2;
			if (middle >= position)
				leftVertex->Add(position, value);
			else
				rightVertex->Add(position, value);
		}
	}

	T operator () (int l, int r)
	{
		if (left > r || right < l) return 0;
		if (left >= l && right <= r) return sum;

		return (*leftVertex)(l, r) + (*rightVertex)(l, r);
	}

	private:

		int left, right, sum;
		std::unique_ptr<SegmentTree> leftVertex, rightVertex;

	void createChildren()
	{
		int middle = (left + right) / 2;
		leftVertex = std::make_unique<SegmentTree>(left, middle);
		rightVertex = std::make_unique<SegmentTree>(middle + 1, right);
	}
};
