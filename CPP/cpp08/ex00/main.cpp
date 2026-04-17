
#include <iostream>
#include <vector>
#include <list>
#include "easyfind.hpp"

int main(void) {
	std::vector<int> v;
	v.push_back(10);
	v.push_back(20);
	v.push_back(30);
	v.push_back(40);
	
	std::vector<int>::iterator it = v.begin();
	std::vector<int>::iterator ite = v.end();
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	try {
		std::vector<int>::iterator it = easyfind(v, 30);
		std::cout << "Found 30 in vector at: " << (it - v.begin()) << std::endl;
	}
	catch (std::exception const &e) {
		std::cout << "vector - " << e.what() << std::endl;
	}
	
	try {
		std::vector<int>::iterator it = easyfind(v, 0);
		std::cout << "Found 30 in vector at: " << (it - v.begin()) << std::endl;
	}
	catch (std::exception const &e) {
		std::cout << "vector - " << e.what() << std::endl;
	}
	
	std::list<int> lst;
	lst.push_back(100);
	lst.push_back(200);
	lst.push_back(300);
	
	std::list<int>::iterator lstIt = lst.begin();
	std::list<int>::iterator lstIte = lst.end();
	while (lstIt != lstIte) {
		std::cout << *lstIt << std::endl;
		++lstIt;
	}
	
	try {
		std::list<int>::iterator it = easyfind(lst, 200);
		std::cout << "Found 400 in list at: " << *it << std::endl;
	}
	catch (std::exception const &e) {
		std::cout << "list - " << e.what() << std::endl;
	}
	
	try {
		std::list<int>::iterator it = easyfind(lst, 2000);
		std::cout << "Found 400 in list at: " << *it << std::endl;
	}
	catch (std::exception const &e) {
		std::cout << "list - " << e.what() << std::endl;
	}
	
	return 0;
}
