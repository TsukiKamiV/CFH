//
//  Contact.cpp
//  phonebook
//
//  Created by Luyao Xu on 01/10/2025.
//

#include "Contact.hpp"

Contact::Contact()
	: _firstName(""), _lastName(""), _nickName(""), _phoneNumber(""), _darkestSecret("")
{}

Contact::~Contact(){}

void	Contact::fillFirstName(const std::string str){
	_firstName = str;
}

void	Contact::fillLastName(const std::string str){
	_lastName = str;
}

void	Contact::fillNickName(const std:: string str){
	_nickName = str;
}

void	Contact::fillPhoneNumber(const std::string str){
	_phoneNumber = str;
}


void	Contact::fillDarkestSecret(const std::string str){
	_darkestSecret = str;
}

const	std::string &Contact::getFirstName() const{
	return (_firstName);
}

const	std::string &Contact::getLastName() const{
	return (_lastName);
}

const	std::string &Contact::getNickName() const{
	return (_nickName);
}

const	std::string &Contact::getPhoneNumber() const{
	return (_phoneNumber);
}

const	std::string &Contact::getDarkestSecret() const{
	return (_darkestSecret);
}
