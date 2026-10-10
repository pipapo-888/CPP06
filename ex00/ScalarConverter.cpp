#include <iostream>
#include <cstdlib>
#include <iomanip>
#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter(){}

ScalarConverter::ScalarConverter(const ScalarConverter&){}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}

ScalarConverter::~ScalarConverter(){}

void ScalarConverter::convert(const std::string &str)
{
	double num = std::strtod(str.c_str(), NULL);
	char c = std::atoi(str.c_str());
	int n = c;

	std::cout << num << std::endl;

    std::cout << "char: " << c <<std::endl;
 
    std::cout << "int: " << n << std::endl;
 
    std::cout << "float: " << std::fixed << std::setprecision(1) << num << "f" <<std::endl;
 
    std::cout << "double: " << std::fixed << std::setprecision(1) << num << std::endl;

}