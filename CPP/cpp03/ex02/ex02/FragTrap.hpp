#ifndef FragTrap_hpp
#define FragTrap_hpp

#include "ClapTrap.hpp"

class FragTrap : public ClapTrap {
public:
	FragTrap();
	FragTrap(const std::string &name);
	FragTrap(const FragTrap &other);
	FragTrap &operator=(const FragTrap &other);
	~FragTrap();
	
	void	attack(const std::string &target);
	void	highFivesGuys(void);
};

#endif
