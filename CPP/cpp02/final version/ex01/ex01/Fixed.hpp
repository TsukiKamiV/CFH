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
	
private:
	int	_rawBits;
	static const int	_fracBits = 8;
};

std::ostream &operator<<(std::ostream &os, const Fixed &value); 

#endif
