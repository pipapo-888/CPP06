#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <sstream>
#include <cctype>
#include <climits>
#include <cmath>
#include "ScalarConverter.hpp"

enum Type {
    CHAR,
    INT,
    FLOAT,
    DOUBLE,
    INVALID
};

ScalarConverter::ScalarConverter(){}
ScalarConverter::ScalarConverter(const ScalarConverter&){}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter&){return *this;}
ScalarConverter::~ScalarConverter(){}

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

static bool isDoubleStr(const std::string &s)
{
    size_t i = 0;
    int dotCount = 0, digitCount = 0;

    if (s[i] == '+' || s[i] == '-')
        i++;
    if (i == s.length())
        return false;
    for (; i < s.length(); i++)
    {
        if (s[i] == '.')
            dotCount++;
        else if (!std::isdigit(s[i]))
            return false;
        else
            digitCount++;
    }
    return dotCount == 1 && digitCount > 0;
}

static bool isPseudo(const std::string &s)
{
    return s == "nan" || s == "nanf" || s == "+inf" || s == "+inff"
        || s == "-inf" || s == "-inff";
}

static Type parseType(const std::string &str)
{
    char lastC = str[str.length() - 1];

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
    if (isDoubleStr(str))
        return DOUBLE;
    if ((lastC == 'f' || lastC == 'F') && isDoubleStr(str.substr(0, str.length() - 1)))
        return FLOAT;
    return INVALID;
}

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

static void printFloat(float f)
{
	std::cout << "float: " << formatFloating(f) << "f" << std::endl;
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
	if (type == FLOAT)
		d = static_cast<float>(d);

	printChar(d);
	printInt(d);
	printFloat(static_cast<float>(d));
	printDouble(d);
}

