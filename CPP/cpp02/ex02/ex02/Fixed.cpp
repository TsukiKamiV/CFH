//
//  Fixed.cpp
//  ex02
//
//  Created by Luyao Xu on 09/10/2025.
//

#include "Fixed.hpp"

Fixed::Fixed(): _rawBits(0) {
	//std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : _rawBits(0) {
	//std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
	//std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		this->_rawBits = other._rawBits;
	}
	return *this;
}

Fixed::~Fixed() {
	//std::cout << "Destructor called" << std::endl;
}

/*====================ADDED IN EX01======================*/

Fixed::Fixed(int n) {
	//std::cout << "Int constructor called" << std::endl;
	this->_rawBits = n << _fracBits;
}

Fixed::Fixed(float f) {
	//std::cout << "Float constructor called" << std::endl;
	int times256 = (1 << _fracBits);
	float	f_tmp = f * times256;
	float	rf_tmp = roundf(f_tmp);
	this->_rawBits = static_cast<int>(rf_tmp);
}

float	Fixed::toFloat(void) const {
	return static_cast<float>(this->_rawBits) / static_cast<float>(1 << _fracBits);
}

int	Fixed::toInt(void) const {
	return this->_rawBits >> _fracBits;
}

int	Fixed::getRawBits(void) const {
	//std::cout << "getRawBits member function called" << std::endl;
	return this->_rawBits;
}

void Fixed::setRawBits(int const raw) {
	this->_rawBits = raw;
}

std::ostream &operator<< (std::ostream &os, const Fixed &value) {
	os << value.toFloat();
	return os;
}

/*==================ADDED IN EX02========================*/
/**
 *@brief “隐式左操作数”：this
 *当Fixed a(10)
 *	Fixed b(5)
 *	if (a > b)
 *	...
 *	编译器会把它翻译成“a.operator>(b)
 *	rhs:right-hand side
 */
bool	Fixed::operator>(const Fixed &rhs) const {
	return this->_rawBits > rhs._rawBits;
}

bool	Fixed::operator<(const Fixed &rhs) const {
	return this->_rawBits < rhs._rawBits;
}

bool	Fixed::operator>=(const Fixed &rhs) const {
	return this->_rawBits >= rhs._rawBits;
}

bool	Fixed::operator<=(const Fixed &rhs) const {
	return this->_rawBits <= rhs._rawBits;
}

bool	Fixed::operator==(const Fixed &rhs) const {
	return this->_rawBits == rhs._rawBits;
}

bool	Fixed::operator!=(const Fixed &rhs) const {
	return this->_rawBits != rhs._rawBits;
}

Fixed	Fixed::operator+(const Fixed &rhs) const {
	Fixed	res;
	res.setRawBits(this->_rawBits + rhs._rawBits);
	return res;
}

Fixed	Fixed::operator-(const Fixed &rhs) const {
	Fixed	res;
	res.setRawBits(this->_rawBits - rhs._rawBits);
	return res;
}

Fixed	Fixed::operator*(const Fixed &rhs) const {
	Fixed	res;
	long long	tmp = static_cast<long long>(this->_rawBits) * rhs._rawBits;
	res.setRawBits(static_cast<int>(tmp >> _fracBits));
	return res;
}

Fixed	Fixed::operator/(const Fixed &rhs) const {
	Fixed	res;
	if (rhs._rawBits == 0) {
		std::cerr << "You cannot devide a number by zero!" << std::endl;
		return res;
	}
	long long	tmp = (static_cast<long long>(this->_rawBits) << _fracBits) / rhs._rawBits;
	res.setRawBits(static_cast<int>(tmp));
	return res;
}

Fixed&	Fixed::operator++(void) {
	this->_rawBits += 1;
	return *this;
}

Fixed	Fixed::operator++(int) {
	Fixed	tmp(*this);
	this->_rawBits += 1;
	return tmp;
}

Fixed&	Fixed::operator--(void) {
	this->_rawBits -= 1;
	return *this;
}

Fixed	Fixed::operator--(int) {
	Fixed	tmp(*this);
	this->_rawBits -= 1;
	return tmp;
}

Fixed &Fixed::min(Fixed &a, Fixed &b) {
	return (a._rawBits < b._rawBits) ? a : b;
}

const Fixed &Fixed::min(const Fixed &a, const Fixed &b) {
	return (a._rawBits < b._rawBits) ? a : b;
}

Fixed &Fixed::max(Fixed &a, Fixed &b) {
	return (a._rawBits > b._rawBits) ? a : b;
}

const Fixed &Fixed::max(const Fixed &a, const Fixed &b) {
	return (a._rawBits > b. _rawBits) ? a : b;
}
