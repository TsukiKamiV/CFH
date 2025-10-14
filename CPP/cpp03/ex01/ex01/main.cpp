#include "ScavTrap.hpp"

int main(void)
{
	std::cout << "\n=== Test 1: Basic construction and attack ===" << std::endl;
	ScavTrap st1("Serena");
	st1.attack("enemy1");
	st1.takeDamage(30);
	st1.beRepaired(20);
	st1.guardGate();
	
	std::cout << "\n=== Test 2: Energy and HP exhaustion ===" << std::endl;
	st1.takeDamage(200);	//instance's _hitPoint down to 0
	st1.attack("enemy2");	//impossible to attack
	st1.beRepaired(10);		//impossible to repair
	
	std::cout << "\n=== Test 3: Copy constructor ===" << std::endl;
	ScavTrap st2(st1);		// call of copy constructor
	st2.attack("enemy3");
	
	std::cout << "\n=== Test 4: Copy assignment ===" << std::endl;
	ScavTrap st3("Guardian");
	st3 = st1;				// call of copy assignment operator
	st3.guardGate();
	
	std::cout << "\n=== End of main, destructors will now be called ===" << std::endl;
	return 0;
}
