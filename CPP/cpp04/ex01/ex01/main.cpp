#include "Animal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"

int main(void) {
	std::cout << "===============Original main function===============" << std::endl;
	const Animal* j = new Dog();
	const Animal* i = new Cat();
	
	delete j;
	delete i;
	
	std::cout << std::endl;
	std::cout << "===============Creation of the animal array===============" << std::endl;
	Animal* animals[10];
	for(int i = 0; i < 10; i++) {
		if (i % 2 == 0)
			animals[i] = new Dog();
		else
			animals[i] = new Cat();
	}
	std::cout << std::endl;
	std::cout << "===============Starting to delete animals===============" << std::endl;
	for (int i = 0; i < 10; i++)
		delete animals[i];
	std::cout << "===============All animals deleted===============" << std::endl;
	return 0;
}
