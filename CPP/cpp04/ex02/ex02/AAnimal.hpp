#ifndef AAnimal_hpp
#define AAnimal_hpp

#include <iostream>
#include <string>

class AAnimal {
public:
	AAnimal();
	AAnimal(const AAnimal &other);
	AAnimal &operator=(const AAnimal &other);
	virtual ~AAnimal();
	
	virtual void	makeSound() const = 0;
	const std::string 	&getType() const;
	
protected:
	std::string	type;
};
#endif
