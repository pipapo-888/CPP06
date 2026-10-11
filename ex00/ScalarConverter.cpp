#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include "ScalarConverter.hpp"


ScalarConverter::ScalarConverter(){}
ScalarConverter::ScalarConverter(const ScalarConverter&){}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}
ScalarConverter::~ScalarConverter(){}

enum Type {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

static bool isIntStr(const std::string &s)
{
	size_t i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (i == s.length())
		return false;
	for (; i < s.length(); i++)
		if (!std::isdigit(s[i]))
			return false;
	return true;
}

static Type parseType(const std::string &str)
{
	if (str == "nanf" || str == "+inff" || str == "-inff")
		return FLOAT;
	if (str == "nan" || str == "+inf" || str == "-inf")
		return DOUBLE;
	if (str.length() == 3 && str[0] == '\'' && str[2] == '\'')
		return CHAR;
	if (str.length() == 1 && !std::isdigit(str[0]))
		return CHAR;
	if (isIntStr(str))
		return INT;
	

	return INVALID;
}



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
	parseType(str);


	char *end = NULL;
	// bool fFlag = false;
	if (str.length() == 1 && !std::isdigit(str[0]))
	{
		// char c = str[0];
	}
	double num = std::strtod(str.c_str(), &end);
	if (strlen(end) == 1 && (end[0] == 'f' || end[0] == 'F')) {
		// fFlag = true;
	} else if (end == str || *end != '\0') {
		std::cout << "strtodに失敗しました\n";
		return ;
	}
		

	char c = std::atoi(str.c_str());
	int n = c;

    std::cout << "char: " << toCharStr(n) <<std::endl;
    std::cout << "int: " << n << std::endl;
    std::cout << "float: " << std::fixed << std::setprecision(1) << static_cast<float>(num) << "f" <<std::endl;
    std::cout << "double: " << std::fixed << std::setprecision(1) << num << std::endl;
}


//todo ./convert "'3'" 　←これの対策するかどうか