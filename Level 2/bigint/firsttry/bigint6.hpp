#pragma once
#include <iostream>
#include <algorithm>
#include <string>

class bigint
{
	private: 
		std::string num;
	
	public:
		bigint() : num("0"){}
		bigint(size_t n) : num(std::to_string(n)){}
		bigint(std::string n)
		{
			if (n.empty() || !(std::all_of(n.begin(), n.end(), ::isdigit)) || (n.size() > 1 && n[0] == '0'))
			{
				std::cout << "Invalid String" << std::endl;
				num = "0";
			}
			else
				num = n;
		}
		bigint(const bigint &oth) : num(oth.num) {}

		friend std::ostream &operator<<(std::ostream &os, const bigint &b)
		{
			os << b.num;
			return (os);
		}

		std::string add_strings(const std::string s1, const std::string s2) const
		{
			int carry = 0;
			std::string result;
			int i = s1.size() - 1; 
			int j = s2.size() - 1;
			while (i >= 0 || j >= 0 || carry)
			{
				int sum = (i >= 0 ? s1[i--] - '0' : 0) + (j >= 0 ? s2[j--] - '0' : 0) + carry;
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

		bigint operator++(int)
		{
			bigint tmp(*this);
			++(*this);
			return (tmp);
		}

		bigint &operator++()
		{
			return (*this += bigint(1));
		}

		bigint &operator<<=(size_t shift)
		{
			num = num + std::string(shift, '0');
			return (*this);
		}

		bigint operator<<(size_t shift) const
		{
			return(bigint(num + std::string(shift, '0')));
		}

		bigint &operator>>=(const bigint &oth)
		{
			if (bigint(num.size()) <= oth)
				num = "0";
			else
			{
				bigint i(0);
				while (i < oth)
				{
					num = num.substr(0, num.size() - 1);
					i++;
				}
			}
			return (*this);
		}

		bool operator<(const bigint &oth) const
		{
			if (num.size() < oth.num.size())
				return (1);
			else if (num.size() > oth.num.size())
				return (0);
			else
				return (num < oth.num);
		}

		bool operator>(const bigint &oth) const
		{
			return !(*this < oth);
		}

		bool operator<=(const bigint &oth) const
		{
			return !(*this > oth);
		}

		bool operator>=(const bigint &oth) const
		{
			return !(*this < oth);
		}

		bool operator==(const bigint &oth) const
		{
			return (num == oth.num);
		}

		bool operator!=(const bigint &oth) const
		{
			return (num != oth.num);
		}

		bigint operator-(const bigint &oth) const
		{
			(void)oth;
			return (bigint());
		}
};