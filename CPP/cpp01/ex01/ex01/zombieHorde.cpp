#include "Zombie.hpp"

/**
 *@new: dynamically allocate memories on the heap, calling the constructor function
 *return value: the pointer pointing to the newly allocated memory object
 *@nothrow: throw any abnormal memory allocation (std::bac_alloc)
 *@this: for every non-static function, the compiler passes a pointer "this", used to access a member function or a member variable
 *if the variable type is "Zombie", the type of "this" ->Zombie*
 */

Zombie* zombieHorde(int N, std::string name) {
	if (N <= 0) 
		return NULL;
	
	Zombie *horde = new (std::nothrow) Zombie[N];
	if (horde == NULL) 
		return NULL;
	
	for (int i = 0; i < N; i++)
		horde[i].setName(name);
	return horde;
}
