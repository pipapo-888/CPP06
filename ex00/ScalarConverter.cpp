#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <climits>
#include <cmath>
#include <limits>
#include "ScalarConverter.hpp"
#include "converterUtils.hpp"


ScalarConverter::ScalarConverter(){}
ScalarConverter::ScalarConverter(const ScalarConverter&){}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}
ScalarConverter::~ScalarConverter(){}

static void printChar(double d)
{
	std::cout << "char: ";
	if (d < 0  || d > 127)
		std::cout << "impossible";
	else if (std::isprint(d))
		std::cout << "\'" << static_cast<char>(d) << "\'";
	else
		std::cout << "Non displayable";

	std::cout << std::endl;
}

static void printInt(double d)
{
	std::cout << "int: ";
	if (d > INT_MAX || d < INT_MIN)
		std::cout << "impossible";
	else
		std::cout << static_cast<int>(d);

	std::cout << std::endl;

}

static std::string formatFloating(double d)
{
	std::ostringstream oss;
	if (d == std::floor(d))
		oss << std::fixed << std::setprecision(1);
	oss << d;
	return oss.str();
}

static bool isFloatOverflow(double d)
{
	double a = std::fabs(d);
	return a > std::numeric_limits<float>::max()
		&& a != std::numeric_limits<double>::infinity();
}

static void printFloat(double d)
{
	// このタイミングでfloat max チェックをしようとおもってたんだけどすでにキャスとされてるからおそいのか
	std::cout << "float: ";
	if (isFloatOverflow(d))
		std::cout << "impossible";
	else
		std::cout << formatFloating(static_cast<float>(d)) << "f";
	std::cout << std::endl;
}

static void printDouble(double d)
{
	std::cout << "double: " << formatFloating(d) << std::endl;
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
	if (type == FLOAT && !isFloatOverflow(d))
		d = static_cast<float>(d);

	printChar(d);
	printInt(d);
	printFloat(d);
	printDouble(d);
}
