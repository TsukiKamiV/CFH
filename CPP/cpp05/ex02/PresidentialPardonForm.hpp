#ifndef PresidentialPardonForm_hpp
#define PresidentialPardonForm_hpp

#include "AForm.hpp"
#include <iostream>

class PresidentialPardonForm : public AForm {
public:
	PresidentialPardonForm();
	PresidentialPardonForm(const std::string &target);
	PresidentialPardonForm(const PresidentialPardonForm &other);
	PresidentialPardonForm &operator=(const PresidentialPardonForm &other);
	~PresidentialPardonForm();
	
private:
	std::string	_target;
	virtual void	doExecute() const;
};

#endif
