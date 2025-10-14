//
//  DiamondTrap.hpp
//  ex03
//
//  Created by Luyao Xu on 10/10/2025.
//

#ifndef DiamondTrap_hpp
#define DiamondTrap_hpp

#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

class DiamondTrap : public ScavTrap, public FragTrap{
public:
	DiamondTrap();
	DiamondTrap(const std::string &name);
	DiamondTrap(const DiamondTrap &other);
	DiamondTrap &operator=(const DiamondTrap &other);
	~DiamondTrap();
	
	void	whoAmI();
	void	attack(const std::string &target);
	
private:
	std::string _name;
};

#endif /* DiamondTrap_hpp */
