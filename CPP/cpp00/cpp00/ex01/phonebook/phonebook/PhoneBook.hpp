//
//  PhoneBook.hpp
//  phonebook
//
//  Created by Luyao Xu on 01/10/2025.
//

#ifndef PhoneBook_hpp
#define PhoneBook_hpp

#include <iostream>
#include <string>
#include <cctype>
#include <iomanip>
#include <sstream>
#include "Contact.hpp"

class PhoneBook{
	
public:
	PhoneBook();
	~PhoneBook();
	
	void	addContact();
	bool	safeGetLine(const std::string &prompt, std::string &out);
	
	//void	removeOldest();
	void	searchContact();
	void	printTable() const;
	void	printIndex();
	void	printOne(const int idx);
	
private:
	Contact _contacts[8];
	int	_count;
	int	_nextIndex;
	//phonebook display formatting
	//static	std::string formatField(const std::string &str);
	bool	isBlank(const std::string &s);
	static	std::string formatField(const std::string &s);
};

#endif /* PhoneBook_hpp */
