//
//  fixed.cpp
//  ex00
//
//  Created by Luyao Xu on 08/10/2025.
//

#include "fixed.hpp"

Fixed::Fixed() : _rawBits(0) {
	std::cout << "Default constructor called" << std::endl;
}

/**
 *@brief 拷贝构造函数：
 *用已有对象初始化新对象时触发
 *Fixed b(a)或Fixed b = a;
 *被赋值对象刚刚创建
 *无返回值
 *用于初始化新对象
 */

Fixed::Fixed(const Fixed &other) {
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

/**
 *@brief 拷贝赋值运算：
 *"当一个已存在的对象 this 被另一个同类型对象 other 赋值时（用 =），执行这个函数。"
 *用已有对象给已存在对象赋值时触发
 *被赋值对象已经存在（而非在初始化阶段）
 *b = a
 *通常返回的是*this（引用）
 *用于更新已有对象的状态
 */
Fixed &Fixed:: operator=(const Fixed &other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		this->_rawBits = other.getRawBits();
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int	Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->_rawBits;
}

void Fixed::setRawBits(int const raw) {
	this->_rawBits = raw;
}
