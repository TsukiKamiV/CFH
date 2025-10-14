
#include "ClapTrap.hpp"

ClapTrap::ClapTrap():_name("default"), _hitPoints(10), _energyPoints(10), _attackDamage(0) {
	std::cout << "ClapTrap default constructor called" << std::endl;
}
ClapTrap::ClapTrap(std::string name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0){
	std::cout << "ClapTrap constructor called for " << this->_name << std::endl;
}
ClapTrap::ClapTrap(const ClapTrap &other) :
	_name(other._name),
	_hitPoints(other._hitPoints),
	_energyPoints(other._energyPoints),
	_attackDamage(other._attackDamage) {
	std::cout << "ClapTrap copy constructor called for " << this->_name << std::endl;
}
ClapTrap &ClapTrap::operator=(const ClapTrap &other) {
	if (this != &other) {
		this->_name = other._name;
		this->_hitPoints = other._hitPoints;
		this->_energyPoints = other._energyPoints;
		this->_attackDamage = other._attackDamage;
	}
	std::cout << "ClapTrap copy assignment operator called for " << this->_name << std::endl;
	return *this;
}
ClapTrap::~ClapTrap() {
	std::cout << "ClapTrap destructor called for " << this->_name << std::endl;
}

void	ClapTrap::attack(const std::string& target) {
	if (this->_hitPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " cannot attack anymore due to 0 hit points" << std::endl;
		return ;
	}
	if (this->_energyPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " cannot attack anymore due to 0 energy points" << std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	std::cout << "ClapTrap " << this->_name << " attacks " << target << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

std::string ClapTrap::getName(void) const {
	return this->_name;
}

std::ostream &operator<< (std::ostream &os, const ClapTrap &clap) {
	os << clap.getName();
	return os;
}

void	ClapTrap::takeDamage(unsigned int amount) {
	if (this->_hitPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " can no longer take any damage, its hit points are already down to zero" << std::endl;
		return ;
	}
	if (amount > this->_hitPoints) {
		this->_hitPoints = 0;
		std::cout << "ClapTrap " << this->_name << " passed out after taking " << amount << " points of damage." << std::endl;
	}
	else {
		this->_hitPoints -= amount;
		std::cout << "ClapTrap " << this->_name << " takes " << amount << " points of damage, " << this->_hitPoints << " hit points remaining." << std::endl;
	}
}
void	ClapTrap::beRepaired(unsigned int amount) {
	if (this->_energyPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " cannot repair itself, energy point 0" << std::endl;
		return ;
	}
	if (this->_hitPoints == 0) {
		std::cout << "ClapTrap " << this->_name << " cannot be repaired because it has no hit points left." << std::endl;
		return ;
	}
	this->_hitPoints += amount;
	this->_energyPoints--;
	std::cout << "ClapTrap " << this->_name << " repaired itself for " << amount << " hit points. It now has " << this->_hitPoints << " hit points" << std::endl;
}
