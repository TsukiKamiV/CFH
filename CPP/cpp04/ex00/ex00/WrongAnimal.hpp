#ifndef WrongAnimal_hpp
#define WrongAnimal_hpp

#include <iostream>

class WrongAnimal{
protected:
	std::string	type;
	
public:
	WrongAnimal();
	WrongAnimal(const WrongAnimal &other);
	WrongAnimal &operator=(const WrongAnimal &other);
	~WrongAnimal();
	
	void	makeSound() const;
	const std::string	&getType() const;
};

#endif /* WrongAnimal_hpp */
