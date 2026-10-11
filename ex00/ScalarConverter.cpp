#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter(){}

ScalarConverter::ScalarConverter(const ScalarConverter&){}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}

ScalarConverter::~ScalarConverter(){}

 static std::string toCharStr(int n)
 {
	if (n < 0 || n > 127)
		return ("impossible");
	if (std::isprint(n))
		return (std::string("'") + static_cast<char>(n) + std::string("'") );
	return ("Non displayable");
 }

void ScalarConverter::convert(const std::string &str)
{
	char *end = NULL;
	double num = std::strtod(str.c_str(), &end);
	if 

	else if (end == str || *end != '\0')
	{
		std::cout << "strtodに失敗しました\n";
		return ;
	}
		

	char c = std::atoi(str.c_str());
	int n = c;

	std::cout << num << std::endl;

    std::cout << "char: " << toCharStr(n) <<std::endl;

    std::cout << "int: " << n << std::endl;
 
    std::cout << "float: " << std::fixed << std::setprecision(1) << num << "f" <<std::endl;
 
    std::cout << "double: " << std::fixed << std::setprecision(1) << num << std::endl;

}