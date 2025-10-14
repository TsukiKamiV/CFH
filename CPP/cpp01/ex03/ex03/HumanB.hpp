#ifndef HumanB_hpp
#define HumanB_hpp

#include "Weapon.hpp"

class HumanB {
public:
	HumanB(const std::string &name);
	~HumanB();
	
	void	attack() const;
	void	setWeapon(Weapon &weapon);
	
private:
	std::string name;
	Weapon	*weapon;
	//不能像HumanA一样写成Weapon &weapon，因为引用（&）必须在对象创建的时候就已经完成初始化，不能在创建以后再赋值
	//而HumanB在题目中与A的不同点就在于“A在构造函数中就拿武器，但B不一定一直拿着武器”
	//指针可以指向一个空的武器指针
};
#endif /* HumanB_hpp */
