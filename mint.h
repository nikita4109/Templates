#include <iostream>

int inverse(int x, int mod)
{
	int u = 0, v = 1;
	while (x)
	{
		int t = mod / x;
		mod -= t * x;
		std::swap(x, mod);
		u -= t * v;
		std::swap(u, v);
	}

	return u;
}

class mint
{
	public:

	int value, mod;

	mint() { value = 0, mod = 1e9 + 7; }
	mint(int _mod) { mod = _mod; }
	mint(int _value, int _mod)
	{
		mod = _mod;
		value = (_value + mod) % mod;
	}

	mint operator + (const mint& other)
	{
		return mint(value + other.value, mod);
	}

	mint operator - (const mint& other)
	{
		return mint(value - other.value, mod);
	}

	mint operator * (const mint& other)
	{
		return mint(value * other.value, mod);
	}

	mint operator / (const mint& other)
	{
		return mint(value * inverse(other.value, mod), mod);
	}

	mint operator += (const mint& other)
	{
		return *this + other;
	}

	mint operator -= (const mint& other)
	{
		return *this - other;
	}

	mint operator *= (const mint& other)
	{
		return *this * other;
	}

	mint operator /= (const mint& other)
	{
		return *this / other;
	}
};

std::istream& operator >> (std::istream& stream, mint& number)
{
	stream >> number.value;

	return stream;
}

std::ostream& operator << (std::ostream& stream, mint number)
{
	stream << number.value;

	return stream;
}
