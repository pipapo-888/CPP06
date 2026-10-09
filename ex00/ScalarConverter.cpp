#include <iostream>
#include <cstdlib>
#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter(){}

ScalarConverter::ScalarConverter(const ScalarConverter&){}

ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}

ScalarConverter::~ScalarConverter(){}

void ScalarConverter::convert(std::string &str)
{
	long num = std::strtod(str.c_str(), NULL);



    std::cout << "char" << std::endl;
 
    std::cout << "int" << std::endl;
 
    std::cout << "float" << std::endl;
 
    std::cout << "double" << std::endl;

}