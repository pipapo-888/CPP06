#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cctype>
#include <climits>
#include <cmath>
#include <limits>
#include <sstream>
#include "ScalarConverter.hpp"
#include "converterUtils.hpp"


ScalarConverter::ScalarConverter(){}
ScalarConverter::ScalarConverter(const ScalarConverter&){}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}
ScalarConverter::~ScalarConverter(){}

static std::string toCharStr(double d)
{
	if (d < 0 || d > 127)
		return ("impossible");
	if (std::isprint(static_cast<int>(d)))
		return (std::string("'") + static_cast<char>(d) + std::string("'"));
	return ("Non displayable");
}

static std::string toIntStr(double d)
{
	if (d < INT_MIN || d > INT_MAX)
		return ("impossible");
	std::ostringstream oss;
	oss << static_cast<int>(d);
	return (oss.str());
}

static std::string toFloatingStr(double d)
{
	std::ostringstream oss;
	if (d == std::numeric_limits<double>::infinity())
		oss << "+inf";
	else if (d == -std::numeric_limits<double>::infinity())
		oss << "-inf";
	else if (d == std::floor(d) && std::fabs(d) < 1e16)
		oss << std::fixed << std::setprecision(1) << d;
	else
		oss << d;
	return (oss.str());
}

static void printInvalid()
{
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: impossible" << std::endl;
	std::cout << "double: impossible" << std::endl;
}

static void printPseudo(const std::string &s, Type type)
{
	std::string base = (type == FLOAT) ? s.substr(0, s.length() - 1) : s;
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	std::cout << "float: " << base << "f" << std::endl;
	std::cout << "double: " << base << std::endl;
}

void ScalarConverter::convert(const std::string &str)
{
	Type type = parseType(str);
	if (type == INVALID)
	{
		printInvalid();
		return ;
	}
	if (isPseudo(str))
	{
		printPseudo(str, type);
		return ;
	}

	double d;
	if (type == CHAR)
		d = (str.length() == 3) ? str[1] : str[0];
	else
		d = std::strtod(str.c_str(), NULL);
	if (type == FLOAT)
		d = static_cast<float>(d);

	std::cout << "char: " << toCharStr(d) << std::endl;
	std::cout << "int: " << toIntStr(d) << std::endl;
	std::cout << "float: " << toFloatingStr(static_cast<float>(d)) << "f" << std::endl;
	std::cout << "double: " << toFloatingStr(d) << std::endl;
}


//todo ./convert "'3'" 　←これの対策するかどうか