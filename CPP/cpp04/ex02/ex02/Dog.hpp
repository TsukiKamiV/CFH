#ifndef Dog_hpp
#define Dog_hpp

#include "AAnimal.hpp"
#include "Brain.hpp"

class Dog : public AAnimal {
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
