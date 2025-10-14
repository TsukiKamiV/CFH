#ifndef Animal_hpp
#define Animal_hpp

#include <iostream>

class Animal {
public:
	Animal();
	Animal(const Animal &other);
	Animal &operator=(const Animal &other);
	virtual ~Animal();
	
	virtual void	makeSound() const;
	const std::string 	&getType() const;
	
protected:
	std::string	type;
};
#endif /* Animal_hpp */
