
#include "ScalarConverter.hpp"

bool	ScalarConverter::isPseudoLiteral(const std::string &input) {
	return input == "nan" || input == "nanf" ||
	input == "+inf" || input == "-inf" ||
	input == "+inff" || input == "-inff";
}

bool	ScalarConverter::isCharLiteral(const std::string &input) {
	return (input.length() == 1 && std::isprint(input[0]) && !std::isdigit(input[0]));
}

bool	ScalarConverter::isIntLiteral(const std::string &input) {
	if (input.empty())
		return false;
	size_t	i = 0;
	if (input[0] == '+' || input[0] == '-')
		i++;
	if (i == input.size())
		return false;
	while (i < input.size()) {
		if (!std::isdigit(static_cast<unsigned char>(input[i])))
			return false;
		i++;
	}
	return true;
}

bool	ScalarConverter::isFloatLiteral(const std::string &input) {
	if (input.empty())
		return false;
	if (input.back() != 'f')
		return false;
	const std::string numPart = input.substr(0, input.size() - 1);
	if (numPart.empty())
		return false;
	size_t	i = 0;
	if (numPart[i] == '+' || numPart[i] == '-') {
		++i;
		if (i == numPart.size())
			return false;
	}
	bool	digitFlag = false;
	bool	dotFlag = false;
	for (; i < numPart.size(); ++i) {
		unsigned char c = static_cast<unsigned char>(numPart[i]);
		if (numPart[i] == '.') {
			if (dotFlag)
				return false;
			dotFlag = true;
			continue;
		}
		if (!std::isdigit(c))
			return false;
		digitFlag = true;
	}
	return (dotFlag && digitFlag);
}

bool	ScalarConverter::isDoubleLiteral(const std::string &input) {
	if (input.empty())
		return false;
	if (input.back() == 'f')
		return false;
	size_t	i = 0;
	if (input[i] == '+' || input[i] == '-')
		++i;
	if (i == input.size())
		return false;
	bool	digitFlag = false;
	bool	dotFlag = false;
	for(; i < input.size(); ++i) {
		unsigned char c = static_cast<unsigned char>(input[i]);
		if (input[i] == '.') {
			if (dotFlag)
				return false;
			dotFlag = true;
			continue;
		}
		if (!std::isdigit(c))
			return false;
		digitFlag = true;
	}
	return (dotFlag && digitFlag);
}
