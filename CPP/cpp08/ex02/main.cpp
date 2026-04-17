
#include <iostream>
#include <list>
#include "MutantStack.hpp"

int main(void) {
	std::cout << "*** Original subject tests ***" << std::endl;
	MutantStack<int>	mstack;
	
	mstack.push(5);
	mstack.push(17);
	
	std::cout << "mstack.top = ";
	std::cout << mstack.top() << std::endl;
	
	mstack.pop();
	
	std::cout << "mstack.size = ";
	std::cout << mstack.size() << std::endl;
	
	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	
	mstack.push(0);
	
	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();
	
	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}
	std::stack<int> s(mstack);
	
	std::cout << "\n*** Comparing with list<int> ***" << std::endl;
	std::list<int> lst;
	lst.push_back(5);
	lst.push_back(17);
	std::cout << "Last added element: " << lst.back() << std::endl;//17
	lst.pop_back();//'17' removed
	std::cout << "List length after pop: " << lst.size() << std::endl;//1
	
	lst.push_back(3);
	lst.push_back(5);
	lst.push_back(737);
	lst.push_back(0);
	std::cout << "*List*" << std::endl;
	for (std::list<int>::iterator it = lst.begin(); it != lst.end(); ++it)
		std::cout << *it << std::endl;
	return 0;
}
