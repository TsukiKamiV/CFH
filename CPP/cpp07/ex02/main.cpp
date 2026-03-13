
#include <iostream>
#include "Array.hpp"

#define MAX_VAL 4
int main(int, char**)
{
	//Array<int> numbers(MAX_VAL);
	//int* mirror = new int[MAX_VAL];
	//srand(time(NULL));
	//for (int i = 0; i < MAX_VAL; i++)
	//{
	//	const int value = rand();
	//	std::cout << value << std::endl;
	//	numbers[i] = value;
	//	mirror[i] = value;
	//}
	//////SCOPE
	//{
	//	Array<int> tmp = numbers;
	//	Array<int> test(tmp);
	//}
	//
	//for (int i = 0; i < MAX_VAL; i++)
	//{
	//	if (mirror[i] != numbers[i])
	//	{
	//		std::cerr << "didn't save the same value!!" << std::endl;
	//		return 1;
	//	}
	//}
	//try
	//{
	//	numbers[-2] = 0;
	//}
	//catch(const std::exception& e)
	//{
	//	std::cerr << e.what() << '\n';
	//}
	//try
	//{
	//	numbers[MAX_VAL] = 0;
	//}
	//catch(const std::exception& e)
	//{
	//	std::cerr << e.what() << '\n';
	//}
	//
	//for (int i = 0; i < MAX_VAL; i++)
	//{
	//	numbers[i] = rand();
	//}
	//delete [] mirror;
	
	std::cout << "===== Test 1: Default constructor (empty array) =====" << std::endl;
	Array<int> empty;
	std::cout <<"empty.size(): " << empty.size() << std::endl;
	try {
		std::cout << empty[empty.size()] << std::endl;
	}
	catch (std::exception &e) {
		std::cout << "Correctly caught exception: " << e.what() << std::endl;
	}
	
	std::cout << "\n===== Test 2: Array(n) constructor =====" << std::endl;
	Array<int> a(5);
	for (size_t	i = 0; i < a.size(); i++)
		a[i] = (int)i * 10;
	printArray(a, "Array<int> a");
	
	std::cout << "\n===== Test 3: Deep copy by copy constructor =====" << std::endl;
	Array<int> b(a);
	b[0] = 999;
	
	printArray(a, "Array a (should not change");
	printArray(b, "Array b (first element should be different");
	
	std::cout << "\n===== Test 4: Deep copy by assignment operator =====" << std::endl;
	Array<int> c;
	c = a;
	c[1] = 4242;
	printArray(a, "Array a (should not change");
	printArray(c, "Array c (second element should be different");
	
	std::cout << "\n===== Test 5: Const array access =====" << std::endl;
	const Array<int> constArr(a);
	std::cout << "(constArr copied from int array a)" << std::endl;
	std::cout << "constArr[2] = " << constArr[2] << std::endl;
	return 0;
}
