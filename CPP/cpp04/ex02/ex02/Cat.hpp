#ifndef Cat_hpp
#define Cat_hpp

#include "AAnimal.hpp"
#include "Brain.hpp"

class Cat : public AAnimal {
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
