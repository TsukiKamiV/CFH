
#ifndef ShrubberyCreationForm_hpp
#define ShrubberyCreationForm_hpp

#include "AForm.hpp"
#include <fstream>
#include <iostream>

class ShrubberyCreationForm : public AForm {
public:
	ShrubberyCreationForm();
	ShrubberyCreationForm(const std::string &target);
	ShrubberyCreationForm(const ShrubberyCreationForm &other);
	ShrubberyCreationForm &operator=(const ShrubberyCreationForm &other);
	~ShrubberyCreationForm();
	
	
private:
	std::string	_target;
	
	virtual	void	doExecute() const;
};

#endif
