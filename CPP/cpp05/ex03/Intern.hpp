
#ifndef Intern_hpp
#define Intern_hpp

#include <iostream>
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

class Intern {
	
public:
	Intern();
	Intern(const Intern &other);
	Intern &operator=(const Intern &other);
	~Intern();
	
	/**
	 *makeForm
	 *@brief This function takes two strings as parameters: the first one represents the name of a form, and the second one represents the target of the form. It returns a pointer to a AForm object (corresponding to the form name passed as a parameter), with its target initialized to the second parameter.
	 */
	AForm *makeForm(const std::string &formName, const std::string &target);
	
	//定义一个新的类型名 t_creator，它代表一种“指向函数的指针类型”——
	//这种函数：
	//•	接收一个 const std::string & 参数
	//•	返回一个 AForm*
	//这种函数签名是：AForm* f(const std::string &param);
	typedef AForm* (*t_formMaker)(const std::string &);
	
	class WrongFormNameException : public std::exception {
	public:
		const char *what() const throw();
	};
};

#endif
