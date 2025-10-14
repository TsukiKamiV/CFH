#include "AAnimal.hpp"
#include "Cat.hpp"
#include "Dog.hpp"
#include "Brain.hpp"

int main(void) {
	std::cout << "===============Original main function===============" << std::endl;
	const AAnimal* j = new Dog();
	const AAnimal* i = new Cat();
	
	/*the AAnimal class cannot be instanciated due to its abstract nature*/
	//AAnimal a;
	//AAnimal* b = new Animal();
	
	delete j;
	delete i;
	
	std::cout << std::endl;
	std::cout << "===============Creation of the animal array===============" << std::endl;
	AAnimal* animals[10];
	for(int i = 0; i < 10; i++) {
		if (i % 2 == 0){
			animals[i] = new Dog();
			animals[i]->makeSound();
		}
		else {
			animals[i] = new Cat();
			animals[i]->makeSound();
		}
	}
	std::cout << std::endl;
	std::cout << "===============Starting to delete animals===============" << std::endl;
	for (int i = 0; i < 10; i++)
		delete animals[i];
	std::cout << "===============All animals deleted===============" << std::endl;
	return 0;
}
