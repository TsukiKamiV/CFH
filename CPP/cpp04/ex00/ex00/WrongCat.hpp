#ifndef WrongCat_hpp
#define WrongCat_hpp

#include "WrongAnimal.hpp"
class WrongCat : public WrongAnimal {
public:
	WrongCat();
	WrongCat(const WrongCat &other);
	WrongCat &operator=(const WrongCat &other);
	~WrongCat();
	
	void	makeSound() const;
};
#endif
