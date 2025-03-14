#pragma once
#include <iostream>

class vect2
{
	private:
		int x;
		int y;

	public:
		vect2() : x(0), y(0) {}
		vect2(x, y) : x(x), y(y) {}
		vect2(const vect2 &oth) : x(oth.x), y(oth.y) {}
		vect2 &operator=(const vect2 &oth)
		{
			if (*this != oth)
			{
				x = oth.x;
				y = oth.y;
			}
			return (*this)
		}

		int operator[](int i) const
		{
			return (i == 0 ? x : y);
		}

		int &operator[](int i)
		{
			return (i == 0 ? x : y);
		}

		friend std::ostream &operator<<(std::ostream &os, const vect2 v)
		{
			os << "{" << v[0] << ", " << v[1] << "}";
			return (os);
		}

		vect2 &operator++()
		{
			x++;
			y++;
			return (*this);
		}

		vect2 operator++(int)
		{
			vect2 tmp(*this);
			x++;
			y++;
			return (tmp);
		}

		
		vect2 &operator--()
		{
			x--;
			y--;
			return (*this);
		}

		vect2 operator++(int)
		{
			vect2 tmp(*this);
			x--;
			y--;
			return (tmp);
		}

		vect2 &operator+=(const vect2 &oth)
		{
			x += oth.x;
			y += oth.y;
			return (*this);
		}

		vect2 &operator-=(const vect2 &oth)
		{
			x -= oth.x;
			y -= oth.y;
			return (*this);
		}

		vect2 operator+(int i) const
		{
			return (vect2(x + i, y + i));
		}

		vect2 operator-(int i) const
		{
			return (vect2(x - i, y - i));
		}

		vect2 operator*(int i) const
		{
			return (vect2(x * i, y * i));
		}

		friend vect2 operator*(const vect2 &oth, int i)
		{
			return (vect2(oth.x * i, oth.y * i));
		}

		vect2 &operator*=(int i)
		{
			x *= i;
			y *= i;
			return (*this);
		}

}