
#include "ScalarConverter.hpp"
#include <iostream>
#include <limits>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <iomanip>

ScalarConverter::ScalarConverter() {
	std::cout << GREEN << "ScalarConverter default constructor called" << RESET << std::endl;
}

ScalarConverter::ScalarConverter(const ScalarConverter &other) {
	(void)other;
	std::cout << GREEN << "ScalarConverter copy constructor called" << RESET << std::endl;
}
ScalarConverter &ScalarConverter::operator=(const ScalarConverter &other) {
	(void)other;
	std::cout << GREEN << "ScalarConverter copy assignment operator called" << RESET << std::endl;
	return (*this);
}
ScalarConverter::~ScalarConverter() {
	std::cout << CYAN << "ScalarConverter destructor called" << RESET << std::endl;
}

std::string ScalarConverter::trimInput(const std::string &input) {
	size_t	start = 0;
	size_t	end = input.size();
	
	while (start < end && std::isspace(static_cast<unsigned char>(input[start])))
		start++;
	while (end > start && std::isspace(static_cast<unsigned char>(input[end - 1 ])))
		end--;
	return input.substr(start, end - start);
}

ScalarConverter::Type ScalarConverter::parseInput(const std::string &input) {
	if (isPseudoLiteral(input))
		return PSEUDO_LITERAL;
	else if (isCharLiteral(input))
		return CHAR;
	else if (isIntLiteral(input))
		return INT;
	else if (isFloatLiteral(input))
		return FLOAT;
	else if (isDoubleLiteral(input))
		return DOUBLE;
	else
		return INVALID;
}

void	ScalarConverter::convert(const std::string &input) {
	std::string trimmedInput = ScalarConverter::trimInput(input);
	Type type = ScalarConverter::parseInput(trimmedInput);
	
	switch (type) {
		case CHAR:
			charConversion(static_cast<char>(trimmedInput[0]));
			break;
		case INT: {
			errno = 0;
			char *end;
			long longValue = std::strtol(trimmedInput.c_str(), &end, 10);
			if (errno == ERANGE || longValue > INT_MAX || longValue < INT_MIN || *end != '\0') {
				double doubleValue = std::strtod(trimmedInput.c_str(), NULL);
				doubleConversion(doubleValue);
			}
			else
				intConversion(static_cast<int>(longValue));
			break;
		}
		case FLOAT:
			floatConversion(static_cast<float>(std::atof(trimmedInput.c_str())));
			break;
		case DOUBLE:
			doubleConversion(std::atof(trimmedInput.c_str()));
			break;
		case PSEUDO_LITERAL:
			handlePseudoLiteral(trimmedInput);
			break;
		case INVALID:
			std::cerr << RED << "char: impossible" << std::endl;
			std::cerr << RED << "int: impossible" << std::endl;
			std::cerr << RED << "float: impossible" << std::endl;
			std::cerr << RED << "double: impossible" << RESET << std::endl;
			break;
	}
}
