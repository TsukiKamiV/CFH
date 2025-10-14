//
//  Zombie.hpp
//  ex01
//
//  Created by Luyao Xu on 04/10/2025.
//

#ifndef Zombie_hpp
#define Zombie_hpp

#include <iostream>
#include <string>
#include <cctype>
#include <sstream>

class Zombie {
	
public:
	Zombie();
	~Zombie();
	
	void	announce(void);
	void	setName(const std::string &name);
	
private:
	std::string name;
};

Zombie*	zombieHorde(int N, std::string name);

#endif /* Zombie_hpp */
