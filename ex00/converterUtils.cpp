#include <cctype>
#include "converterUtils.hpp"

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

bool isPseudo(const std::string &s)
{
	return s == "nan" || s == "nanf" || s == "+inf" || s == "+inff"
		|| s == "-inf" || s == "-inff";
}

Type parseType(const std::string &str)
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
