//
//  Zombie.cpp
//  playground.cpp
//
//  Created by Luyao Xu on 03/10/2025.
//

#include "Zombie.hpp"

Zombie::Zombie(std::string name): name(name){};
Zombie::~Zombie() {
	std::cout << name << " has been destroyed." << std::endl;
}

void	Zombie::announce() {
	std::cout << name << ": Brainzzzzzzzz..." << std::endl;
}
