
#include "Weapon.hpp"
#include "HumanA.hpp"
#include "HumanB.hpp"

int main() {
	{
		Weapon club = Weapon("crude spiked club");
		
		HumanA bob("Bob", club);
		bob.attack();
		club.setType("some other type of club");
		bob.attack();
	}
	
	{
		Weapon club = Weapon("crude spiked club");
		
		HumanB jim("Jim");
		jim.setWeapon(club);//这里虽然是把HumanB的指针指向了club，但club是在stack上创建的，不需要delete
		jim.attack();
		club.setType("some other type of club");
		jim.attack();
	}
	return 0;
}
