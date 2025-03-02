#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class bigint
{
	private:
		std::string num;

	public:
		bigint() : num("0") {}
		bigint(size_t n) : num(std::to_string(n)) {}
		bigint(const bigint &oth) : num(oth.num) {}
		bigint(const std::string &n)
		{
			if (n.empty() || !std::all_of(n.begin(), n.end(), ::isdigit) || n.size() > 1 && n[0] == '0')
			{
				std::cout << "invalid string" << std::endl;
				num = "0";
			}
			else
			{
				num = n;
			}
		}

		friend std::ostream &operator<<(std::ostream &os, bigint &b)
		{
			os << b.num;
			return (os);
		}

		std::string add_strings(const std::string &n1, const std::string &n2) const
		{
			std::string result;
			int carry = 0;
			int i = n1.size() - 1;
			int j = n2.size() - 1;
			while (i >= 0 || j >= 0 || carry)
			{
				int sum = (i >= 0 ? n1[i--] - '0' : 0) + (j >= 0 ? n2[j--] - '0' : 0) + carry;
				result.push_back(sum % 10 + '0');
				carry = sum / 10;
			}
			std::reverse(result.begin(), result.end());
			return (result);
		}

		bigint operator+(const bigint &oth) const
		{
			return (bigint(add_strings(num, oth.num)));
		}

		bigint &operator+=(const bigint &oth)
		{
			num = add_strings(num, oth.num);
			return (*this);
		}









};