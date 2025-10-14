//
//  PhoneBook.cpp
//  phonebook
//
//  Created by Luyao Xu on 01/10/2025.
//

#include "PhoneBook.hpp"

PhoneBook::PhoneBook(){
	_count = 0;
	_nextIndex = 0;
}

PhoneBook::~PhoneBook(){}

void	PhoneBook::addContact(){
	Contact c;
	std::string input;
	
	do {
		if (!safeGetLine("Enter first name: ", input))
			return ;
	}	while (input.empty() || isBlank(input));
	c.fillFirstName(input);
	
	do {
		if (!safeGetLine("Enter last name: ", input))
			return ;
	}	while (input.empty() || isBlank(input));
	c.fillLastName(input);
	
	do {
		if (!safeGetLine("Enter nickname: ", input))
			return ;
	}	while (input.empty() || isBlank(input));
	c.fillNickName(input);
	
	do {
		if (!safeGetLine("Enter phone number: ", input))
			return ;
	}	while (input.empty() || isBlank(input));
	c.fillPhoneNumber(input);
	
	do {
		if (!safeGetLine("Enter darkest secret: ", input))
			return ;
	}	while (input.empty() || isBlank(input));
	c.fillDarkestSecret(input);
	
	_contacts[_nextIndex] = c;
	_nextIndex = (_nextIndex + 1) % 8;
	if (_count < 8)
		_count++;
	std::cout << "Contact added successfully!" << std::endl;
}

void	PhoneBook::searchContact(){
	//先把所有已经保存在数组中的联系人信息全部按照格式打印
		//先打印出表头
		//算出当前字符串的长度，如果大于10就交给单独的裁剪函数
		//先写一个"|"，再把这个字符串从最后一位开始从右往左写进当前行，不足10字符的用空格填满，直到一行全写完（单个联系人的所有信息）
		//对列表中每个联系人做完以上操作
	//通过prompt获取index
	//如果index小于等于_count，就把那个联系人打印出来（一个项目一行，打印完整信息）；如果大于_count或者输入不合法，就输出一个报错信息
	if (_count == 0){
		std::cout << "The phonebook is empty.\n" << std::endl;
		return ;
	}
	PhoneBook::printTable();
	PhoneBook::printIndex();
}

void	PhoneBook::printTable()const{
	std::cout << std::setw(10) << std::right << "Index" << "|"
			  << std::setw(10) << std::right << "First" << "|"
			  << std::setw(10) << std::right << "Last" << "|"
			  << std::setw(10) << std::right << "Nickname" << std::endl;
	
	for (int i = 0; i < _count; i++){
		std::string first = _contacts[i].getFirstName();
		std::string last = _contacts[i].getLastName();
		std::string nick = _contacts[i].getNickName();
		
		if (first.length() > 10)
			first = first.substr(0, 9) + ".";
		if (last.length() > 10)
			last = first.substr(0, 9) + ".";
		if (nick.length() > 10)
			nick = nick.substr(0, 9) + ".";
		
		std::cout << std::setw(10) << std::right << i << "|"
				  << std::setw(10) << std::right << first << "|"
				  << std::setw(10) << std::right << last << "|"
		<< std::setw(10) << std::right << nick << std::endl;
	}
}

void	PhoneBook::printIndex(){
	std::cout << "There are currently " << _count << " contacts in the phonebook\n" << std::endl;
	while (true)
	{
		std::string input;
		do {
			if (!safeGetLine("Please enter the index of your choice: ", input))
				return ;
		}	while (input.empty() || isBlank(input));
		int	index;
		std::istringstream ss(input);
		if (!(ss >> index)) {
			std::cout << "Invalid index input, non digit input detected.\n";
			continue ;
		}
		if (index < 0 || index >= _count) {
			std::cout << "Index out of range.\n";
			continue ;
		}
		PhoneBook::printOne(index);
		break;
	}
	return ;
}

void	PhoneBook::printOne(const int idx)
{
	std::cout << "First name: " << _contacts[idx].getFirstName() << "\n";
	std::cout << "Last name: " << _contacts[idx].getLastName() << "\n";
	std::cout << "Nickname: " << _contacts[idx].getNickName() << "\n";
	std::cout << "Phone number: " << _contacts[idx].getPhoneNumber() << "\n";
	std::cout << "Darkest secret: " << _contacts[idx].getDarkestSecret() << std::endl;
}

bool	PhoneBook::safeGetLine(const std::string &prompt, std::string &out){
	std::cout << prompt;
	if (!std::getline(std::cin, out))
		return (false);
	return (true);
}

bool	PhoneBook::isBlank(const std::string &s){
	for (size_t i = 0; i < s.length(); i++){
		if (!std::isspace(static_cast<unsigned char>(s[i])))
			return (false);
	}
	return (true);
}
