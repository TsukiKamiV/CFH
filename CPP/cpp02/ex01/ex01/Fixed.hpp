//
//  Fixed.hpp
//  ex01
//
//  Created by Luyao Xu on 08/10/2025.
//

#ifndef Fixed_hpp
#define Fixed_hpp

#include <stdio.h>
#include <iostream>

class Fixed {
public:
	Fixed();
	Fixed(const Fixed &other);
	Fixed &operator=(const Fixed &other);
	~Fixed();
	/**
	 *函数重载（Function overload):
	 *同一个函数名，可以根据参数的数量、类型或者顺序的不同而定义多个版本（构造函数和一般函数都可以重载）
	 */
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

#endif /* Fixed_hpp */
