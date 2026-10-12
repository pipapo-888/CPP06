#ifndef CONVERTERUTILS_HPP
#define CONVERTERUTILS_HPP

#include <string>

enum Type {
	CHAR,
	INT,
	FLOAT,
	DOUBLE,
	INVALID
};

Type parseType(const std::string &str);
bool isPseudo(const std::string &s);

#endif
