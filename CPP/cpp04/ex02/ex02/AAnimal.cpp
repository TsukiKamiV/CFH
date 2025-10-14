#include "AAnimal.hpp"

AAnimal::AAnimal() : type("AAnimal") {
	std::cout << "AAnimal default constructor called" << std::endl;
}

AAnimal::AAnimal(const AAnimal &other) : type(other.type) {
	std::cout << "AAnimal copy constructor called" << std::endl;
}

AAnimal &AAnimal::operator=(const AAnimal &other) {
	if (this != &other)
		this->type = other.type;
	std::cout << "AAnimal copy assignment operator called" << std::endl;
	return *this;
}

AAnimal::~AAnimal() {
	std::cout << "AAnimal destructor called" << std::endl;
}

const std::string	&AAnimal::getType() const {
	return this->type;
}

//Deletion of the below function because the Animal class is abstract
//void	Animal::makeSound() const {
//	std::cout << "🦄Some random animal sound...🦄" << std::endl;
//}
