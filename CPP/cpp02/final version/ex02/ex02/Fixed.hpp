#ifndef Fixed_hpp
#define Fixed_hpp

#include <iostream>
#include <cmath>
#include <cfloat>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed &other);
	Fixed &operator=(const Fixed &other);
	~Fixed();
	
	Fixed(int n);
	Fixed(float f);
	
	float	toFloat(void) const;
	int		toInt(void) const;
	
	int		getRawBits(void) const;
	void 	setRawBits(int const raw);
	
	bool	operator>(const Fixed &rhs) const;
	bool	operator<(const Fixed &rhs) const;
	bool	operator>=(const Fixed &rhs) const;
	bool	operator<=(const Fixed &rhs) const;
	bool	operator==(const Fixed &rhs) const;
	bool	operator!=(const Fixed &rhs) const;
	
	Fixed	operator+(const Fixed &rhs) const;
	Fixed	operator-(const Fixed &rhs) const;
	Fixed	operator*(const Fixed &rhs) const;
	Fixed	operator/(const Fixed &rhs) const;

	Fixed	&operator++();
	Fixed	operator++(int);
	Fixed	&operator--();
	Fixed	operator--(int);
	
	/**@brief A static member function min that takes two references to fixed-point numbers as parameters, and returns a reference to the smallest one.*/
	static Fixed &min(Fixed &a, Fixed &b);
	/**@brief A static member function min that takes two references to constant fixed-point numbers as parameters, and returns a reference to the smallest one.*/
	static const Fixed &min(const Fixed &a, const Fixed &b);
	/**@brief A static member function max that takes two references to fixed-point numbers as parameters, and returns a reference to the greatest one.*/
	static Fixed &max(Fixed &a, Fixed &b);
	/**@brief A static member function max that takes two references to constant fixed-point numbers as parameters, and returns a reference to the greatest one.*/
	static const Fixed &max(const Fixed &a, const Fixed &b);

	
private:
	int	_rawBits;
	static const int	_fracBits = 8;
};

std::ostream &operator<<(std::ostream &os, const Fixed &value); 
#endif
