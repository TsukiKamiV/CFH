#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>
//#include <cctype>
#include <iomanip>

void	ScalarConverter::handleChar(char input) {
	if (isprint(static_cast<unsigned char>(input)))
		std::cout << "Char: '" << input << "'"<< std::endl;
	else
		std::cout << "char: non displayable" << std::endl;
}

void	ScalarConverter::handleInt(int input) {
	std::cout << "Int: " << input << std::endl;
}

void	ScalarConverter::handleFloat(float input) {
	std::cout << "Float: " << std::fixed << std::setprecision(1) << input << "f" << std::endl;
}

void	ScalarConverter::handleDouble(double input) {
	std::cout << "Double: " << std::fixed << std::setprecision(1) << input << std::endl;
}

void	ScalarConverter::handlePseudoLiteral(const std::string &input) {
	std::cout << "char: impossible" << std::endl;
	std::cout << "int: impossible" << std::endl;
	if (input == "nanf" || input == "nan") {
		std::cout << "float: nanf" << std::endl;
		std::cout << "double: nan" << std::endl;
	}
	else if (input == "+inff" || input == "+inf") {
		std::cout << "float: +inff" << std::endl;
		std::cout << "double: +inf" << std::endl;
	}
	else if (input == "-inff" || input == "-inf") {
		std::cout << "float: -inff" << std::endl;
		std::cout << "double: -inf" << std::endl;
	}
	else {
		std::cout << "float: impossible" << std::endl;
		std::cout << "double: impossible" << std::endl;
	}
}
