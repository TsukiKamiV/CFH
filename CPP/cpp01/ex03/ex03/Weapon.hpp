#ifndef Weapon_hpp
#define Weapon_hpp

#include <stdio.h>
#include <iostream>
#include <string>

class Weapon {
	
public:
	Weapon(const std::string &type);
	~Weapon();
	
	const 	std::string& getType() const;
	void	setType(const std::string &type);//more efficient, avoid duplicating the existing variable
	
private:
	std::string type;
};

#endif /* Weapon_hpp */
