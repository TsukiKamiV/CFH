//
//  Zombie.hpp
//  playground.cpp
//
//  Created by Luyao Xu on 03/10/2025.
//

#ifndef Zombie_hpp
#define Zombie_hpp

#include <iostream>

class Zombie{
	
public:
	Zombie(std::string name);
	~Zombie();
	
	void	announce(void);
	
private:
	std::string	name;
};

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

#endif /* Zombie_hpp */
