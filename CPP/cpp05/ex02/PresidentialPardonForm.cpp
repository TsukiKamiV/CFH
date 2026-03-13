#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm(), _target("Default") {
	std::cout << GREEN << "PresidentialPardonForm default constructor called" << RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const std::string &target) : AForm("President", 25, 5), _target(target) {
	std::cout << GREEN << "PresidentialPardonForm Constructor called with target <" << this->_target << ">" << RESET << std::endl;
}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) : AForm(), _target(other._target) {
	std::cout << GREEN << "PresidentialPardonForm copy constructor called" << RESET << std::endl;
}

PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
	if (this != &other)
		this->_target = other._target;
	std::cout << GREEN << "PresidentialPardonForm copy assignment operator called" << RESET << std::endl;
	return *this;
}

PresidentialPardonForm::~PresidentialPardonForm() {
	std::cout << CYAN << "PresidentialPardonForm destructor called" << RESET << std::endl;
}

void	PresidentialPardonForm::doExecute() const {
	std::cout << MAGENTA << "**[" << this->_target << "] has been pardoned by 🕺🏼Zaphod Beeblebrox🖋️**" << RESET << std::endl;
}
