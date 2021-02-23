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

	int value = 0, mod = 1e9 + 7;

	mint() { }
	template<typename T> mint(const T& _val) { value = _val; }

	template<typename T>
	mint(const T& _value, const T& _mod)
	{
		mod = _mod;
		value = (_value + mod) % mod;
	}

	operator int() const { return value; }

	mint operator + (const mint& other) { return mint(value + other.value, mod); }
	mint operator - (const mint& other) { return mint(value - other.value, mod); }
	mint operator * (const mint& other) { return mint(value * other.value, mod); }
	mint operator / (const mint& other) { return mint(value * inverse(other.value, mod), mod); }

	mint operator += (const mint& other) { return *this + other; }
	mint operator -= (const mint& other) { return *this - other; }
	mint operator *= (const mint& other) { return *this * other; }
	mint operator /= (const mint& other) { return *this / other; }

	template <typename T> mint operator % (const T& other) { return mint(value % other, mod); }
	template <typename T> mint operator + (const T& other) { return *this + mint(other, mod); }
	template <typename T> mint operator - (const T& other) { return *this - mint(other, mod); }
	template <typename T> mint operator * (const T& other) { return *this * mint(other, mod); }
	template <typename T> mint operator / (const T& other) { return *this / mint(other, mod); }

	template <typename T> mint operator += (const T& other) { return *this + mint(other, mod); }
	template <typename T> mint operator -= (const T& other) { return *this - mint(other, mod); }
	template <typename T> mint operator *= (const T& other) { return *this * mint(other, mod); }
	template <typename T> mint operator /= (const T& other) { return *this / mint(other, mod); }

	mint operator = (const mint& other)
	{
		value = other.value;
		mod = other.mod;
		return *this;
	}

	template <typename T>
	mint operator = (const T& other)
	{
		value = other;
		return *this;
	}

	mint operator++() { return *this += 1; }
	mint operator--() { return *this -= 1; }
	mint operator++(int) { mint result(*this); *this += 1; return result; }
	mint operator--(int) { mint result(*this); *this -= 1; return result; }
};

template <typename T> mint operator * (T a, mint b) { return b * a; }
template <typename T> mint operator / (T a, mint b) { return mint(a, b.mod) / b; }
template <typename T> mint operator + (T a, mint b) { return mint(a, b.mod) + b; }
template <typename T> mint operator - (T a, mint b) { return mint(a, b.mod) - b; }

std::istream& operator >> (std::istream& stream, mint& number)
{
	stream >> number.value;
	return stream;
}

std::ostream& operator << (std::ostream& stream, const mint& number)
{
	stream << number.value;
	return stream;
}
