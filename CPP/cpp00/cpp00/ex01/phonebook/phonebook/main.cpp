/**
 *You have to implement two classes:
 • PhoneBook
 ◦ It has an array of contacts.
 ◦ It can store a maximum of 8 contacts. If the user tries to add a 9th contact, replace the oldest one by the new one.
 ◦ Please note that dynamic allocation is forbidden. • Contact
 ◦ Stands for a phonebook contact.
 */

#include <iostream>
//#include "Contact.hpp"
#include "PhoneBook.hpp"
#include <string>

int main()
{
	PhoneBook pb;
	std::string	cmd;
	
	while (true)
	{
		if (!pb.safeGetLine("Please enter command: ", cmd))
			break;
		if (cmd == "ADD")
			pb.addContact();
		else if (cmd == "SEARCH")
			pb.searchContact();
		else if (cmd == "EXIT"){
			std::cout << "Exiting the phonebook..."<<std::endl;
			break;
		}
	}
	return 0;
}
