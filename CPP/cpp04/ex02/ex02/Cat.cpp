
#include "Cat.hpp"

Cat::Cat() {
	this->type = "Cat";
	this->brain = new Brain;
	std::cout << "Cat constructor called" << std::endl;
}

Cat::Cat(const Cat &other) : AAnimal(other) {
	//*this = other;
	this->type = other.type;
	this->brain = other.brain;
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat &Cat::operator=(const Cat &other) {
	std::cout << "Cat copy assignment operator called" << std::endl;
	if (this != &other)
		this->type = other.type;
	delete this->brain;
	this->brain = new Brain(*other.brain);
	return *this;
}

Cat::~Cat() {
	delete this->brain;
	std::cout << "Cat destructor called" << std::endl;
}

void	Cat::makeSound() const {
	std::cout << "🐱Meow! Meow!🐱" << std::endl;
}

