#include "DiamondTrap.hpp"

int main(void)
{
	std::cout << "\n=== Test 1: Basic construction and whoAmI ===" << std::endl;
	DiamondTrap d1("Lucy");
	d1.whoAmI();   // 打印 DiamondTrap 与 ClapTrap 的名字
	ScavTrap s1("Tom");
	s1.attack("Jerry");
	
	//std::cout << "\n=== Test 2: Attack & inherited functions ===" << std::endl;
	//d1.attack("target dummy");   // 调用 ScavTrap 的 attack()
	//d1.takeDamage(20);           // 继承自 ClapTrap
	//d1.beRepaired(10);           // 继承自 ClapTrap
	
	//std::cout << "\n=== Test 3: Copy constructor ===" << std::endl;
	//DiamondTrap d2(d1);
	//d2.whoAmI();
	//d2.attack("enemy");
	//
	//std::cout << "\n=== Test 4: Copy assignment ===" << std::endl;
	//DiamondTrap d3("Luna");
	//d3 = d1;   // 测试赋值运算符
	//d3.whoAmI();
	//
	//std::cout << "\n=== Test 5: Energy/HP exhaustion check ===" << std::endl;
	//for (int i = 0; i < 55; i++)  // 消耗掉 EP
	//d1.attack("dummy");
	//d1.beRepaired(5);  // 由于 EP=0，应该提示无法修复
	//
	//std::cout << "\n=== End of tests, destructors will now be called ===" << std::endl;
	return 0;
}
