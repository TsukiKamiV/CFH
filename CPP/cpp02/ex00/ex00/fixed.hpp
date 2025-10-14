//
//  fixed.hpp
//  ex00
//
//  Created by Luyao Xu on 08/10/2025.
//

#ifndef fixed_hpp
#define fixed_hpp

#include <stdio.h>
#include <iostream>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed &other);//a copy of the constructor
	Fixed &operator=(const Fixed &other);//copy of assignment operator
	~Fixed();//destructor
	
	/**
	 *@return: the raw value of the fixed-point value
	 */
	int	getRawBits(void) const;
	
	/**
	 *@brief sets the raw value of the fixed-point number
	 */
	void	setRawBits(int const raw);

private:
	int	_rawBits;//to store the fixed-point number value
	static const int _fracBits = 8; // to store the number of fractional bits. Its value will always be the integer literal 8
	
};

#endif /* fixed_hpp */
