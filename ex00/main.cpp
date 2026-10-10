#include <iostream>
#include "ScalarConverter.hpp"


int main(int ac, char *av[])
{
	if (ac != 2 || av[1][0] == '\0')
	{
		std::cout << "Wrong input\n";
		return 1;
	}
	std::string str = static_cast<std::string>(av[1]);

	ScalarConverter::convert(str);

	// float i = 42.0f;

	// std::cout << i << std::endl;

	return 0;
}
