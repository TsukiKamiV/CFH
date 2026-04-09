
#include "RPN.hpp"

RPN::RPN() {}
RPN::RPN(const RPN &other) : _stack(other._stack) {}
RPN& RPN::operator=(const RPN &other) {
	if (this != &other)
		this->_stack = other._stack;
	return *this;
}
RPN::~RPN() {}

/**
 *std::istringstream >> token ➡️ 按空白分隔，逐个读取字符串token
 */
int		RPN::evaluate(const std::string &param) {
	std::stack<int> empty;
	_stack.swap(empty);
	std::istringstream	iss(param);
	std::string	token;
	int	a, b;
	while (iss >> token) {
		if (token.length() == 1 && std::isdigit(static_cast<unsigned char>(token[0])))
			_stack.push(token[0] - '0');
		else if (token.length() == 1 && (token[0] == '+' || token[0] == '-' || token[0] == '*' || token[0] == '/')) {
			if (_stack.size() < 2)
				throw std::runtime_error("Error: wrong param, not enough numbers to be executed");
			b = _stack.top();
			_stack.pop();
			a = _stack.top();
			_stack.pop();
			if (token[0] == '+')
				_stack.push(a + b);
			else if (token[0] == '-')
				_stack.push(a - b);
			else if (token[0] == '*')
				_stack.push(a * b);
			else {
				if (b == 0)
					throw std::runtime_error("Error: you can't devide a number by 0");
				_stack.push(a / b);
			}
		}
		else
			throw std::runtime_error("Error");
	}
	if (_stack.size() != 1)
		throw std::runtime_error("Error");
	return _stack.top();
}

