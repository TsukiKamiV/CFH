#ifndef Dog_hpp
#define Dog_hpp

#include "Animal.hpp"
#include "Brain.hpp"

class Dog : public Animal {
public:
	Dog();
	Dog(const Dog &other);
	Dog &operator=(const Dog &other);
	~Dog();
	
	void	makeSound() const;
	
private:
	Brain*	brain;
};
#endif /* Dog_hpp */
