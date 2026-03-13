
#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iomanip>

/**
 *char non-displayable: 0-127 (isascii) but !std::isprint
 *char impossible value < 0 || value > 127
 */
void	ScalarConverter::charConversion(char c) {
	handleChar(c);
	handleInt(static_cast<int>(c));
	handleFloat(static_cast<float>(c));
	handleDouble(static_cast<double>(c));
}

void	ScalarConverter::intConversion(int i) {
	if (i < 0 || i > 127)
		std::cout << "char: impossible" << std::endl;
	else
		handleChar(static_cast<char>(i));
	handleInt(i);
	handleFloat(static_cast<float>(i));
	handleDouble(static_cast<double>(i));
}

void	ScalarConverter::floatConversion(float f) {
	if (f < 0.0f || f > 127.0f)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<unsigned char>(static_cast<int>(f))))
		std::cout << "char: non displayable" << std::endl;
	else
		handleChar(static_cast<char>(f));
	if (f < static_cast<float>(INT_MIN) || f > static_cast<float>(INT_MAX))
		std::cout << "int: impossible" << std::endl;
	else
		handleInt(static_cast<int>(f));
	handleFloat(f);
	handleDouble(static_cast<double>(f));
}

void	ScalarConverter::doubleConversion(double d) {
	if (d < 0.0 || d > 127.0)
		std::cout << "char: impossible" << std::endl;
	else if (!std::isprint(static_cast<unsigned char>(static_cast<int>(d))))
		std::cout << "char: non displayable" << std::endl;
	else
		handleChar(static_cast<char>(d));
	if (d < static_cast<double>(INT_MIN) || d > static_cast<double>(INT_MAX))
		std::cout << "int: impossible (overflow)" << std::endl;
	else
		handleInt(static_cast<int>(d));
	if (std::fabs(d) > static_cast<double>(std::numeric_limits<float>::max()))
		std::cout << "float: impossible" << std::endl;
	else
		handleFloat(static_cast<float>(d));
	handleDouble(d);
}
