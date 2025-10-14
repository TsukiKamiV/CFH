#include "Zombie.hpp"

int	main() {
	randomChump("STAAAAAAACK");
	Zombie* z2 = newZombie("HHHEEEAAAPPP");
	z2->announce();
	delete z2;
	return 0;
}
