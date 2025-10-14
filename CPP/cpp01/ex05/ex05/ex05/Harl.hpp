//
//  Harl.hpp
//  ex05
//
//  Created by Luyao Xu on 07/10/2025.
//

#ifndef Harl_hpp
#define Harl_hpp

#include <stdio.h>
#include <iostream>

class Harl {
	
	
	
private:
	void	debug(void);
	void	info(void);
	void	warning(void);
	void	error(void);
	
public:
	Harl();
	~Harl();
	void	complain(std::string level);
};

#endif /* Harl_hpp */
