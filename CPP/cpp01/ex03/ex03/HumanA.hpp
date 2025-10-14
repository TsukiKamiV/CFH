#ifndef HumanA_hpp
#define HumanA_hpp

#include "Weapon.hpp"

class HumanA {
public:
	
	HumanA(const std::string &name, Weapon &weapon);
	~HumanA();
	
	void	attack(void) const;
private:
	std::string name;
	Weapon		&weapon;
};

#endif /* HumanA_hpp */
