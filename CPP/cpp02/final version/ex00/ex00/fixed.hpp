#ifndef fixed_hpp
#define fixed_hpp

#include <iostream>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed &other);
	Fixed &operator=(const Fixed &other);
	~Fixed();
	
	int	getRawBits(void) const;
	
	void	setRawBits(int const raw);

private:
	int	_rawBits;
	static const int _fracBits = 8; 
	
};

#endif
