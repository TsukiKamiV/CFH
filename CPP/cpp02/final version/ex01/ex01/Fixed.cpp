#include "Fixed.hpp"

Fixed::Fixed(): _rawBits(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed &other) : _rawBits(0) {
	std::cout << "Copy constructor called" << std::endl;
	*this = other;
}

Fixed &Fixed::operator=(const Fixed &other) {
	std::cout << "Copy assignment operator called" << std::endl;
	if (this != &other) {
		this->_rawBits = other._rawBits;
	}
	return *this;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

/*====================ADDED IN EX01======================*/

Fixed::Fixed(int n) {
	if (n >= (INT_MAX >> _fracBits) || n <= (INT_MIN >> _fracBits)) {
		std::cerr << "Warning: int overflow in Fiexed(int), rawbits manually set to zero" << std::endl;
		this->_rawBits = 0;
	}
	else {
		std::cout << "Int constructor called" << std::endl;
		this->_rawBits = n << _fracBits;
	}
}

Fixed::Fixed(float f) {
	std::cout << "Float constructor called" << std::endl;
	int times256 = (1 << _fracBits);

	/*To avoid float overflow*/
	if (f > (static_cast<float>(INT_MAX) / times256) || f < (static_cast<float>(INT_MIN) / times256)) {
		std::cerr << "Warning: float overflow in Fixed(float), rawbits manually set to zero" << std::endl;
		this->_rawBits = 0;
		return ;
	}
	if (f > FLT_MAX || f < -FLT_MAX) {
		std::cerr << "Warning: input float exceeds FLT_MAX, rawbits manually set to zero" << std::endl;
		this->_rawBits = 0;
		return ;
	}
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
	std::cout << "getRawBits member function called" << std::endl;
	return this->_rawBits;
}

void Fixed::setRawBits(int const raw) {
	this->_rawBits = raw;
}

std::ostream &operator<< (std::ostream &os, const Fixed &value) {
	os << value.toFloat();
	return os;
}
