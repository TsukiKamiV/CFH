
#include <iostream>
#include "iter.hpp"


int main(void) {
	int	arr[] = {1, 2, 3};
	const int	cArr[] = {10, 20, 30, 40, 50, 60};
	std::string str_arr[] = {"Hello", "world", "Bye bye"};
	Point pts[] = {{1, 2}, {3, 4}, {5, 6}};
	Whatever wArr[] = {Whatever(100), Whatever(200), Whatever(300), Whatever(400)};
	std::cout << "**Print int array**" << std::endl;
	::iter(arr, 3, print<int>);
	std::cout << "**Print const int array**" << std::endl;
	::iter(cArr, 6, print<int>);
	std::cout << "**Print string array**" << std::endl;
	::iter(str_arr, 3, print<std::string>);
	std::cout << "**Square int array**" << std::endl;
	::iter(arr, 3, square<int>);
	std::cout << "**Print 2-dimensional point struct array**" << std::endl;
	::iter(pts, 3, print<Point>);
	std::cout << "**Print Whatever class (int) array**" << std::endl;
	::iter(wArr, 4, print<Whatever>);
	return 0;
}


