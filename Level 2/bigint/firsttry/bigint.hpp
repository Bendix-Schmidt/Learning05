#pragma once
#include <iostream>
#include <string>
#include <algorithm>

class bigint
{
	private:
		std::string num;
	
	public:
		bigint(size_t n) : num(std::to_string(n)){}
		bigint() : num("0"){}

}