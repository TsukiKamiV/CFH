#ifndef Cat_hpp
#define Cat_hpp

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal {
public:
	Cat();
	Cat(const Cat &other);
	Cat &operator=(const Cat &other);
	~Cat();
	
	void	makeSound() const;
	
private:
	Brain*	brain;
};
#endif /* Cat_hpp */
