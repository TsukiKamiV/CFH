//
//  main.cpp
//  ex02
//
//  Created by Luyao Xu on 10/10/2025.
//

#include "FragTrap.hpp"

int main(void)
{
	FragTrap ft("Boomer");
	ft.attack("target dummy");
	ft.takeDamage(50);
	ft.beRepaired(30);
	ft.highFivesGuys();
	return 0;
}
