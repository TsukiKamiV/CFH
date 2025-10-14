//
//  ScavTrap.hpp
//  ex01
//
//  Created by Luyao Xu on 10/10/2025.
//

#ifndef ScavTrap_hpp
#define ScavTrap_hpp

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
public:
	ScavTrap();
	ScavTrap(const std::string &name);
	ScavTrap(const ScavTrap &other);
	ScavTrap &operator=(const ScavTrap &other);
	~ScavTrap();

	void	attack(const std::string &target);
	void	guardGate(void);
};
#endif /* ScavTrap_hpp */
