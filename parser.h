#include <vector>
#include <sstream>

template<typename T>
class Parser
{
public:
	Parser(const std::string &s)
	{
		for (int i = 0; i < s.size(); ++i)
		{
			if (s[i] == ' ') continue;
			if (s[i] >= '0' && s[i] <= '9')
			{
				std::string number = "";
				while (i < s.size() && s[i] >= '0' && s[i] <= '9')
				{
					number += s[i];
					++i;
				}

				tokens.push_back(number);
				--i;
			}
			else
			{
				tokens.push_back("");
				tokens.back() += s[i];
			}
		}

		value = EvaluateSum();
	}

	int GetValue() const { return value; }

private:
	std::vector<std::string> tokens;
	int position = 0;
	T value;

	T EvaluateSum()
	{
		T first = EvaluateMul();
		while (position < tokens.size())
		{
			std::string &oper = tokens[position];
			if (oper == "+" || oper == "-")
				++position;
			else
				break;

			T second = EvaluateMul();
			if (oper == "-") second *= -1;
			first += second;
		}

		return first;
	}

	T EvaluateMul()
	{
		T first = EvaluateExpr();
		while (position < tokens.size())
		{
			std::string &oper = tokens[position];
			if (oper == "*" || oper == "/")
				++position;
			else
				break;

			T second = EvaluateExpr();
			if (oper == "*")
				first *= second;
			else
				first /= second;
		}

		return first;
	}

	T EvaluateExpr()
	{
		std::string next = tokens[position];

		int unary = 1;
		if (next == "-") unary *= -1;
		if (next == "+" || next == "-")
		{
			++position;
			return unary * EvaluateExpr();
		}

		if (next == "(")
		{
			++position;
			T result = EvaluateSum();
			++position;
			return result;
		}

		++position;

		std::istringstream stream(next);
		T result;
		stream >> result;

		return result;
	}
};
