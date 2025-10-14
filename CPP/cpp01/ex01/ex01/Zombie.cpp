#include "Zombie.hpp"

Zombie::Zombie() : name("") {}
Zombie::~Zombie() {
	std::cout << name << " has been destroyed after a feast of your delicious brain." << std::endl;
}

void	Zombie::announce() {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void	Zombie::setName(const std::string &name) {
	this->name = name;
}
