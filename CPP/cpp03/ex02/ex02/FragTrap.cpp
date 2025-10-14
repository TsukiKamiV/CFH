#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("default") {
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap default constructor called for " << this->_name << std::endl;
}

FragTrap::FragTrap(const std::string &name) : ClapTrap(name) {
	this->_hitPoints = 100;
	this->_energyPoints = 100;
	this->_attackDamage = 30;
	std::cout << "FragTrap constructor called for " << this->_name << std::endl;
}

FragTrap::FragTrap(const FragTrap &other) : ClapTrap(other) {
	std::cout  << "FragTrap copy constructor called for " << this->_name << std::endl;
}

FragTrap &FragTrap::operator=(const FragTrap &other) {
	if (this != &other) {
		ClapTrap::operator=(other);
	}
	std::cout << "FragTrap copy assignment operator called for " << this->_name << std::endl;
	return *this;
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap destructor called for " << this->_name << std::endl;
}

void	FragTrap::attack(const std::string &target) {
	if (this->_hitPoints == 0) {
		std::cout << "FragTrap " << this->_name << " cannot attack anymore due to 0 hit points" << std::endl;
		return ;
	}
	if (this->_energyPoints == 0) {
		std::cout << "FragTrap " << this->_name << " cannot attack anymore due to 0 energy points" << std::endl;
		return ;
	}
	this->_energyPoints -= 1;
	std::cout << "FragTrap " << this->_name << " stabbed " << target << " with a knife, causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void	FragTrap::highFivesGuys() {
	std::cout << "FragTrap " << this->_name << " is shouting loudly: Gimme a HIGHHHHH FIIIIIIIIVE!!"  << std::endl;
}
