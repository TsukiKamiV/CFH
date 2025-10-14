
#include "ScavTrap.hpp"

ScavTrap::ScavTrap() : ClapTrap("default") {
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap default constructor called for " << this->_name << std::endl;
}

ScavTrap::ScavTrap(const std::string &name) : ClapTrap(name) {
	this->_hitPoints = 100;
	this->_energyPoints = 50;
	this->_attackDamage = 20;
	std::cout << "ScavTrap constructor called for " << this->_name << std::endl;
}

ScavTrap::ScavTrap(const ScavTrap &other) : ClapTrap(other) {
	std::cout  << "ScavTrap copy constructor called for " << this->_name << std::endl;
}

ScavTrap &ScavTrap::operator=(const ScavTrap &other) {
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	std::cout << "ScavTrap copy assignment operator called for " << this->_name << std::endl;
	return *this;
}

ScavTrap::~ScavTrap() {
	std::cout << "ScavTrap destructor called for " << this->_name << std::endl;
}

void	ScavTrap::attack(const std::string &target) {
	if (this->_hitPoints == 0) {
		std::cout << "ScavTrap " << this->_name << " cannot attack anymore due to 0 hit points" << std::endl;
		return ;
	}
	if (this->_energyPoints == 0) {
		std::cout << "ScavTrap " << this->_name << " cannot attack anymore due to 0 energy points" << std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	std::cout << "ScavTrap " << this->_name << " waved its lethal weapon at " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void	ScavTrap::guardGate(void) {
	std::cout << "ScavTrap " << this->_name << " is now in Gate keeper mode." << std::endl;
}
