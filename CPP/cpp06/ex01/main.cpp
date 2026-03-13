
#include <iostream>
#include "Serializer.hpp"
#include "Data.hpp"

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RESET "\033[0m"

int main(void) {
	Data data1;
	data1.name = "";
	data1.age = 6;
	data1.height = 1.2;
	std::cout << YELLOW << "DATA:\n" << "NAME: " << data1.name <<
	 " | AGE: " << data1.age << " | Height: " << data1.height << RESET << std::endl;
	
	uintptr_t raw1 = Serializer::serialize(&data1);
	Data* ptr1 = Serializer::deserialize(raw1);
	std::cout << "Address [original]:  " << GREEN << &data1 << RESET << std::endl;
	std::cout << "Address [serialize]: " << GREEN << ptr1 << RESET << std::endl;
	std::cout << "Comparing pointer addr: " << GREEN << (&data1 == ptr1 ? "SAME" : "DIFFERENT") << RESET << std::endl;;
	std::cout << "Name  : " << GREEN << ptr1->name << RESET << std::endl;
	std::cout << "Age   : " << GREEN << ptr1->age << RESET << std::endl;
	std::cout << "Height: " << GREEN << ptr1->height << RESET << std::endl;
	return 0;
}
