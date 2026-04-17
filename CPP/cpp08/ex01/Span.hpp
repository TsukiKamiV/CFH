
#ifndef span_hpp
#define span_hpp

#include <iostream>
#include <stdexcept>
#include <iterator>
#include <vector>
#include <algorithm>

class Span {
public:
	Span();
	Span(unsigned int N);
	Span(const Span &other);
	Span& operator=(const Span &other);
	~Span();
	
	void	addNumber(const int);
	int		shortestSpan(void);
	int		longestSpan(void);
	
	template <typename InputIterator>
	void	addNumber(InputIterator first, InputIterator last) {
		unsigned int	spaceLeft;
		unsigned int	rangeSize;
		
		if (_storage.size() > _sizeMax)
			throw std::runtime_error("Span internal state invalid");
		spaceLeft = _sizeMax - _storage.size();
		rangeSize = static_cast<unsigned int>(std::distance(first, last));
		if (rangeSize > spaceLeft)
			throw std::runtime_error("Not enough space in Span for range insert");
		_storage.insert(_storage.end(), first, last);
	}
	
private:
	unsigned int 		_sizeMax;
	std::vector<int> 	_storage;
};

#endif
