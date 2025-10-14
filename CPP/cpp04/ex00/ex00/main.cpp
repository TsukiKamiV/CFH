#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

/**
 *@brief 多态（Polymorphism)：相同的接口，不同的实现
 *同一个函数调用makeSound在实际运行时根据对象的真实类型（Dog/Cat)执行不同的版本
 *——静态绑定（static binding）在编译时绑定，非virtual，编译器在编译阶段决定调用哪个函数；
 *——动态绑定（dynamic binding) 在运行时绑定，virtual函数，程序运行时根据对象真实类型选择
 *实现多态的三个条件：
 *1. 继承
 *	必须有父类和子类的层级关系
 *2. 虚函数（virtual）
 *	父类必须把希望“多态化”的函数声明为virtual
 *3. 基类指针或引用
 *	必须通过基类类型（而不是子类类型）访问对象
 *===========================================
 *“继承”是让子类有父类的属性和函数；
 *“多态”是让这些函数能在不同的子类中表现出不同的行为
 */

int main(void) {
	const Animal* meta = new Animal();
	const Animal* j = new Dog();//如果这里写Dog d; d.makeSound();就不是多态，而只是普通调用
	const Animal* i = new Cat();
	
	std::cout << j->getType() << " " << std::endl;
	std::cout << i->getType() << " " << std::endl;
	j->makeSound();
	i->makeSound();
	meta->makeSound();
	delete i;
	delete j;
	delete meta;
	
	/*==================Wrong Animal Class======================*/
	const WrongAnimal* Tom = new WrongCat();
	const WrongAnimal* WrongMeta = new WrongAnimal();
	std::cout << Tom->getType() << ":";
	Tom->makeSound();
	WrongMeta = Tom;
	std::cout << "WrongMeta type: " << WrongMeta->getType() << std::endl;
	delete Tom;
	
	/*==================Wrong Animal Copy=======================*/
	std::cout << "=========================================" << std::endl;
	//WrongAnimal wa;
	WrongCat wc;
	WrongAnimal waCopy(wc);
	//WrongCat wcCopy(wc);
	//std::cout << wa.getType() << ": ";
	//wa.makeSound();
	//std::cout << wc.getType() << ": ";
	//wc.makeSound();
	std::cout << waCopy.getType() << ": ";
	waCopy.makeSound();
	//std::cout << wcCopy.getType() << ": ";
	//wcCopy.makeSound();
	std::cout << "=========================================" << std::endl;
	return 0;
}
