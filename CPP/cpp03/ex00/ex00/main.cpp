//
//  main.cpp
//  ex00
//
//  Created by Luyao Xu on 10/10/2025.
//

#include "ClapTrap.hpp"


int main(void) {
	ClapTrap a ("Tom");
	
	a.attack("Jerry");
	a.takeDamage(5);
	a.beRepaired(3);
	a.attack("Jerry");
	a.takeDamage(20);
	a.attack("Jerry");
	a.beRepaired(5);
	return 0;
}
