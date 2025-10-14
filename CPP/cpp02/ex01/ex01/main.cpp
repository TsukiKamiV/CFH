//
//  main.cpp
//  ex01
//
//  Created by Luyao Xu on 08/10/2025.
//

#include "Fixed.hpp"
#include <iostream>

int main(void) {
	Fixed	a;//默认构造函数，初始化一个Fixed类的a
	/*==============================================================================*/
	/**
	 *@brief//创建一个名为b的常量对象，类型是Fixed，并且在创建时使用参数为10的构造函数来初始化它
	 *等价于Fixed const b = Fixed(10);只是语法风格不同
	 *编译器看到类名 Fixed，知道要创建一个该类型的对象；
	 *括号里有一个参数 10（类型为 int）；
	 *编译器就去查找类 Fixed 中参数列表匹配为 int 的构造函数“Fixed::Fixed(int n);”；
	 *所以在运行到这里会打印“int constructor called"
	 */
	Fixed const b(10);
	/*==============================================================================*/
	Fixed const c(42.42f);
	/*==============================================================================*/
	Fixed const d(b);
	/*==============================================================================*/
	
	/**
	 *@brief 括号里的f是“字面量后缀（literal suffix)”，用于告诉编译器这是个float类型，而不是默认的double
	 */
	a = Fixed(1234.4321f );
	
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	
	return 0;
}
