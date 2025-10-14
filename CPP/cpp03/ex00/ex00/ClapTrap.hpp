//
//  ClapTrap.hpp
//  ex00
//
//  Created by Luyao Xu on 10/10/2025.
//

#ifndef ClapTrap_hpp
#define ClapTrap_hpp

#include <iostream>

class ClapTrap {
	
private:
	std::string  _name;
	unsigned int _hitPoints;
	unsigned int _energyPoints;
	unsigned int _attackDamage;
	
public:
	ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(const ClapTrap &other);
	ClapTrap &operator=(const ClapTrap &other);
	~ClapTrap();
	
	void	attack(const std::string& target);
	void	takeDamage(unsigned int amount);
	void	beRepaired(unsigned int amount);
	std::string getName(void) const;
};

std::ostream &operator<<(std::ostream &os, const ClapTrap &name);
#endif /* ClapTrap_hpp */
