
#include <iostream>
#include <stdexcept>
#include "span.hpp"

int main(void) {
	std::cout << "*** TEST 1: Original main with try/catch from subject ***" << std::endl;
	Span sp = Span(5);
	try {
		sp.addNumber(6);
		sp.addNumber(3);
		sp.addNumber(17);
		sp.addNumber(9);
		sp.addNumber(11);
		//sp.addNumber(20);
	}
	catch (std::exception const &e) {
		std::cerr << e.what() << std::endl;
	}
	
	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;
	
	std::cout << "*** TEST 2: Add several numbers at once ***" << std::endl;
	try {
		Span sp(10);
		int arr[] = {1, 2, 3, 4, 5};
		sp.addNumber(arr, arr + 5);
		std::cout << "longestSpan: " << sp.longestSpan() << std::endl;
		std::cout << "shortestSpan: " << sp.shortestSpan() << std::endl;
	}
	catch (std::exception &e) {
		std::cerr << "Exeption: " << e.what() << std::endl;
	}
	return 0;
}
