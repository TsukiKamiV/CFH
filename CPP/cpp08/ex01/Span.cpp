
#include "Span.hpp"

Span::Span() : _sizeMax(0), _storage() {}
Span::Span(unsigned int N) : _sizeMax(N), _storage() {}
Span::Span(const Span& other) : _sizeMax(other._sizeMax), _storage(other._storage) {}
Span& Span::operator=(const Span &other) {
	if (this != &other) {
		this->_sizeMax = other._sizeMax;
		this->_storage = other._storage;
	}
	return *this;
}
Span::~Span(){}

void	Span::addNumber(const int value) {
	if (this->_storage.size() == _sizeMax)
		throw std::runtime_error ("Span container already full, number adding failed");
	_storage.push_back(value);
}

int		Span::shortestSpan(void) {
	if (_storage.size() < 2)
		throw std::runtime_error("Not enough elements in container");
	
	int	distance = INT_MAX;
	
	std::vector<int> tmp = _storage;
	std::sort(tmp.begin(), tmp.end());
	std::vector<int>::iterator it = tmp.begin();
	std::vector<int>::iterator next = it;
	++next;
	
	while (next != tmp.end()) {
		int diff = *next - *it;
		if (diff < distance)
			distance = diff;
		++it;
		++next;
	}
	return distance;
}

int		Span::longestSpan(void) {
	if (_storage.size() < 2)
		throw std::runtime_error("Not enough elements in container");
	std::vector<int> tmp = this->_storage;
	std::sort(tmp.begin(), tmp.end());
	std::vector<int>::iterator itMin = tmp.begin();
	std::vector<int>::iterator itMax = tmp.end();
	--itMax;
	//std::cout << "MIN: " << *itMin << std::endl;
	//std::cout << "MAX: " << *itMax << std::endl;
	int distance = *itMax - *itMin;
	return distance;
}
