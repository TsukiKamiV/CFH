#include "fixed.hpp"
#include <iostream>

int main(void) {
	Fixed a;
	Fixed b(a);
	Fixed c;
	
	c = b;//这里就是触发拷贝赋值的地方
	
	std::cout << a.getRawBits() << std::endl;
	std::cout << b.getRawBits() << std::endl;
	std::cout << c.getRawBits() << std::endl;
	
	return 0;
}
